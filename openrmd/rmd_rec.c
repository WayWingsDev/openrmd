#include "rmd_rec.h"
#include "rmd.h"
#include "rmd_devmgr.h"
#include "rmd_sessmgr.h"
#include "getcfg.h"
#include "lookup_so.h"
#include "readbuf.h"
#include "single_login.h"
#include "hash.h"
#include "dlist.h"
#include "rtp.h"

#ifdef RMD_HAS_UDS
#include "access/rmd_uds.h"
#endif

/* record state */
#define REC_APPLIED		0x01
#define REC_LOGINED		0x02
#define REC_RECORD		0x04

#define is_applied(x)		(x & REC_APPLIED)
#define is_logined(x)		(x & REC_LOGINED)
#define is_record(x)		(x & REC_RECORD)
#define set_applied(x)		(x |= REC_APPLIED)
#define set_logined(x)		(x |= REC_LOGINED)
#define set_record(x)		(x |= REC_RECORD)
#define set_unapplied(x)	(x &= ~REC_APPLIED)
#define set_unlogined(x)	(x &= ~REC_LOGINED)
#define set_unrecord(x)		(x &= ~REC_RECORD)
#define set_nonestate(x)	(x = 0)

#define DRIVER_TABLE_SIZE	20	/* default driver hash table size */
#define OUT_BUFF_SIZE		(RTP_MTU + RTP_HDR_FIX_SIZE + 20)
#define INTERRUPT_TIMEOUT	20	/* if no data incoming in this time, 
					   interrupt it */

static hash_table_t *driver_table = NULL;  /* record driver hash table */
static dlist_t *rec_task_list = NULL;
static single_login_t *sl = NULL;
static int report_rec_stat = 0;
static int record_type = 0;	/* -1:manual 0:auto 1/2/3:alarm */

static void set_report_rec_stat()
{
	getcfg(cfg_file, "report_rec_stat", &report_rec_stat, GETCFG_INT32);
}

#ifdef RMD_HAS_UDS
static void notify_rec_stat(char *rec_name, int rec_flag)
{
	char buff[128];

	if (report_rec_stat == 0)
		return;

	snprintf(buff, sizeof(buff), "%s%s:%d", 
			RMD_RECSTAT, rec_name, rec_flag);
	rmd_uds_sendmsg(buff, strlen(buff));
}
#endif

static inline unsigned int hash_func_driver(const int table_size, void *data)
{
	rec_driver_t *driver = (rec_driver_t *)data;
	return (unsigned int)driver->type % table_size;
}

static inline int cmp_func_driver(void *data, void *param)
{
	rec_driver_t *driver = (rec_driver_t *)data;
	return (driver->type == (int)param ? 0 : -1);
}

static int login_storage(char *ip, int port, char *user, char *pwd, 
		void *param)
{
	channel_t *channel = (channel_t *)param;
	rec_driver_t *driver = (rec_driver_t *)channel->rec_driver;

	unsigned int loginid = driver->rmd_di_rec_login(ip, port, user, pwd);
	if (loginid == -1)
		syslog(LOG_DEBUG, "[NVR LOGIN] -->>(%s:%d) err:%lu", 
				ip, port, driver->rmd_di_rec_geterror());
	else
		syslog(LOG_DEBUG, "[NVR LOGIN] -->>(%s:%d) success", ip, port);
	return (int)loginid;
}

static int logout_storage(void *data, void *param)
{
	channel_t *channel = (channel_t *)param;
	rec_driver_t *driver = (rec_driver_t *)channel->rec_driver;

	int ret = driver->rmd_di_rec_logout(channel->rec_loginid);
	if (ret == -1)
		syslog(LOG_DEBUG, "[NVR LOGOUT] <<--(%s:%d) failed",
				channel->storage_ip, channel->storage_port);
	else
		syslog(LOG_DEBUG, "[NVR LOGOUT] <<--(%s:%d) success",
				channel->storage_ip, channel->storage_port);
	return ret;
}

static void rec_state_reset(channel_t *channel)
{
	rec_driver_t *driver = (rec_driver_t *)channel->rec_driver;

	if (is_record(channel->rec_state)) {
		driver->rmd_di_rec_stop_record(channel->rec_handle);
		set_unrecord(channel->rec_state);
	}

	if (is_logined(channel->rec_state)) {
		single_logout(sl, logout_storage, channel->storage_ip, 
				channel->storage_port, (void *)channel);
		set_unlogined(channel->rec_state);
	}
}

static inline int record_callback(char *buff, int bytes, void *param)
{
	channel_t *channel = (channel_t *)param;
	rec_driver_t *driver = (rec_driver_t *)channel->rec_driver;
	int ret;

	if (!is_record(channel->rec_state) || channel->rec_error == 1)
		return -1;

	channel->bgn_time = channel->end_time;
	channel->end_time = time(NULL);
	channel->last_data_time = get_runtime();
	if (channel->end_time < channel->bgn_time)
		channel->end_time = channel->bgn_time;

	if (channel->is_rtp_packet) {
		char out_buff[OUT_BUFF_SIZE];
		int out_bytes;

		if (channel->payload_type == RTP_PT_H264) {
			out_bytes = rtp_get_h264_data(buff, bytes, out_buff, 
					OUT_BUFF_SIZE);
			if (out_bytes <= 0)
				return -1;
		} else if (channel->payload_type == RTP_PT_MJPEG) {
			return -1;	/* TODO */
		} else {
			return -1;	/* TODO */
		}

		ret = driver->rmd_di_rec_record(channel->rec_handle, 
				out_buff, out_bytes, channel->bgn_time, 
				channel->end_time);
	} else {
		ret = driver->rmd_di_rec_record(channel->rec_handle, buff, 
				bytes, channel->bgn_time, channel->end_time);
	}

	if (ret != 0) {
		syslog(LOG_DEBUG, "record [%s] error: %lu", channel->rec_name, 
				driver->rmd_di_rec_geterror());
		channel->rec_error = 1;
		return -1;
	}

	return 0;
}

static int add_driver(char *so)
{
	rec_driver_t *driver;
	void *handle;

	handle = dlopen(so, RTLD_LAZY);
	if (handle == NULL) {
		syslog(LOG_DEBUG, "%s", dlerror());
		return -1;
	}

	driver = calloc(1, sizeof(rec_driver_t));
	if (driver == NULL)
		goto err;

	if (!(driver->rmd_di_rec_get_info = 
				dlsym(handle, "rmd_di_rec_get_info"))
			|| !(driver->rmd_di_rec_init = 
				dlsym(handle, "rmd_di_rec_init"))
			|| !(driver->rmd_di_rec_geterror = 
				dlsym(handle, "rmd_di_rec_geterror"))
			|| !(driver->rmd_di_rec_login = 
				dlsym(handle, "rmd_di_rec_login"))
			|| !(driver->rmd_di_rec_logout = 
				dlsym(handle, "rmd_di_rec_logout"))
			|| !(driver->rmd_di_rec_start_record = 
				dlsym(handle, "rmd_di_rec_start_record"))
			|| !(driver->rmd_di_rec_record = 
				dlsym(handle, "rmd_di_rec_record"))
			|| !(driver->rmd_di_rec_stop_record = 
				dlsym(handle, "rmd_di_rec_stop_record"))
			/* ... */)
		goto err;

	if (driver->rmd_di_rec_init(get_runtime) != 0)
		goto err;
	if (driver->rmd_di_rec_get_info(&driver->type) != 0)
		goto err;
	if (hash_add(driver_table, (void *)driver) != 0)
		goto err;

	return 0;

err:
	dlclose(handle);
	if (driver)
		free(driver);
	return -1;
}

static int driver_init()
{
	int n = 0;

	/* initialize hash table */
	driver_table = hash_init(DRIVER_TABLE_SIZE, hash_func_driver);
	if (driver_table == NULL)
		return -1;

	/* load device drivers into hash table */
	char path[PATH_MAX], prefix[32];
	getcfg(cfg_file, "device_lib_path", path, GETCFG_STR);
	getcfg(cfg_file, "device_lib_name_prefix", prefix, GETCFG_STR);

	char *names = lookup_so(path, prefix);
	if (names == NULL) {
		syslog(LOG_ERR, "no driver found");
		return -1;
	}

	buf_t *pb = openbuf(names, strlen(names));
	if (pb == NULL) {
		free(names);
		return -1;
	}

	char *line;
	while ((line = readbuf(pb, "\n")) != NULL) {
		if (add_driver(line) == 0)
			n++;
	}
	closebuf(pb);
	free(names);

	if (n == 0) {
		syslog(LOG_ERR, "none driver loaded");
		return -1;
	}

	return 0;
}

static int add_task(void *data, void *param)
{
	rec_driver_t driver;
	channel_t *channel = (channel_t *)data;
	if (channel->rec != 1)
		return -1;

	driver.type = channel->storage_type;
	if (hash_entry(driver_table, (void *)&driver, cmp_func_driver, 
			(void *)channel->storage_type, 
			(void **)&channel->rec_driver) == -1) {
		syslog(LOG_DEBUG, "none rec driver: %d", channel->storage_type);
		channel->rec = 0;
		return -1;
	}

	if (channel->id == 1)
		snprintf(channel->rec_name, sizeof(channel->rec_name), 
				"IPC_%04d", ((device_t *)channel->pdevice)->id);
	else
		snprintf(channel->rec_name, sizeof(channel->rec_name), 
				"IPC_%04d-%d", 
				((device_t *)channel->pdevice)->id,
				channel->id);

	((rec_driver_t *)channel->rec_driver)->record_callback =
		record_callback;
	set_nonestate(channel->rec_state);
	channel->rec_error = 0;
	if (dlist_add(&rec_task_list, (void *)channel) == -1) {
		channel->rec = 0;
		return -1;
	}
	syslog(LOG_DEBUG, "add rec task:%d %s", 
			channel->storage_type, channel->rec_name);
	return 0;
}

static int task_run_callback(void *data, void *param)
{
	channel_t *channel = (channel_t *)data;
	rec_driver_t *driver = (rec_driver_t *)channel->rec_driver;
	start_record_info_t info;
	int dev_type = ((driver_t *)channel->pdriver)->type;

	/*
	syslog(LOG_DEBUG, "[REC TASK] %s %d %d %d", channel->rec_name, 
			is_applied(channel->rec_state),
			is_logined(channel->rec_state),
			is_record(channel->rec_state));
			*/

	if (!is_applied(channel->rec_state)) {
		if (rmd_sessmgr_play_by_rec(channel) != 0)
			return -1;
		set_applied(channel->rec_state);
	}

	if (is_logined(channel->rec_state)) {
		if (channel->rec_error == 1) {
			syslog(LOG_DEBUG, "interrupt cause record error [%s]",
					channel->rec_name);
			rec_state_reset(channel);
#ifdef RMD_HAS_UDS
			notify_rec_stat(channel->rec_name, REC_FAILED);
#endif
		} else if ((get_runtime() - channel->last_data_time) > 
				INTERRUPT_TIMEOUT) {
			syslog(LOG_DEBUG, "interrupt cause camera error [%s]", 
					channel->rec_name);
			rec_state_reset(channel);
#ifdef RMD_HAS_UDS
			notify_rec_stat(channel->rec_name, REC_FAILED);
#endif
		}
	}

	if (channel->camera_state == 0)
		return -1;	/* no action, until camera become OK */

	if (!is_logined(channel->rec_state)) {
		channel->rec_loginid = single_login(sl, login_storage, 
				channel->storage_ip, channel->storage_port,
				channel->storage_user, channel->storage_pwd,
				(void *)channel);
		if (channel->rec_loginid == -1)
			return -1;
		set_logined(channel->rec_state);
	}

	if (!is_record(channel->rec_state)) {
		if (channel->hdr_buff && channel->hdr_length == 0)
			return -1;  /* the media header not coming yet */

		info.login_id = channel->rec_loginid;
		snprintf(info.record_name, sizeof(info.record_name), 
				channel->rec_name);
		snprintf(info.record_alias, sizeof(info.record_alias), 
				channel->rec_name);
		info.record_type = record_type;
		info.disk_no = channel->storage_disk;
		if (channel->hdr_length > 0) {
			info.hdr_len = channel->hdr_length;
			memcpy(info.hdr_buff, channel->hdr_buff, 
					channel->hdr_length);
		} else {
			/* if the device have no media header, put device type
			 * at the begin (4 bytes). */
			info.hdr_len = 4;
			sprintf(info.hdr_buff, "%04d", dev_type);
		}
		snprintf(info.desc, sizeof(info.desc), channel->rec_name);

		channel->rec_handle = driver->rmd_di_rec_start_record(&info);
		if (channel->rec_handle == -1) {
			syslog(LOG_DEBUG, "start_record [%s] error: %lu", 
					channel->rec_name, 
					driver->rmd_di_rec_geterror());
			rec_state_reset(channel);
			return -1;
		}
		syslog(LOG_DEBUG, "[REC START] %s", channel->rec_name);
		set_record(channel->rec_state);
		channel->end_time = time(NULL);
		channel->rec_error = 0;
		channel->last_data_time = get_runtime();

#ifdef RMD_HAS_UDS
		notify_rec_stat(channel->rec_name, REC_SUCC);
#endif
	}

	return 0;
}

static void *task_scheduler(void *arg)
{
	while (1) {
		dlist_for_each(rec_task_list, task_run_callback, arg);
		sleep(5);
	}
	return NULL;
}

static int task_init()
{
	pthread_t tid;

	rec_task_list = dlist_init();
	rmd_devmgr_travel_channel(add_task, NULL);

	if (dlist_empty(rec_task_list))	/* have none record task */
		return -1;

	sl = single_login_init();
	if (sl == NULL)
		return -1;
	
	if (pthread_create(&tid, NULL, task_scheduler, NULL) != 0)
		return -1;
	pthread_detach(tid);
	return 0;
}

int rmd_rec_start()
{
	set_report_rec_stat();

	if (driver_init() != 0)
		return -1;

	if (task_init() != 0)
		return -1;

	return 0;
}

int rmd_rec_stop()
{
	return 0;
}
