#include "rmd_sessmgr.h"
#include "rmd.h"
#include "rmd_data_callback.h"
#include "dlist.h"
#include "hash.h"
#include "getcfg.h"
#include "udpsock.h"

#ifdef RMD_HAS_REC
#include "rmd_rec.h"
#endif

#include "access/rmd_rtcpsvr.h"
#include "rmd_event.h"

#define SESSION_EMPTY(c) \
	(dlist_empty(c->tcp_clients) && dlist_empty(c->rtp_clients))

static hash_table_t *sess_table = NULL;

#ifdef ENABLE_SESS_MTX
static pthread_mutex_t sess_mtx = PTHREAD_MUTEX_INITIALIZER;
#endif

#ifdef ENABLE_SESS_MTX
#define LOCK_SESS	pthread_mutex_lock(&sess_mtx);
#define UNLOCK_SESS	pthread_mutex_unlock(&sess_mtx);
#else
#define LOCK_SESS
#define UNLOCK_SESS
#endif

#define RTP_MIN_PORT_DEFAULT	12000
#define RTP_MAX_PORT_DEFAULT	20000

static int rtp_min_port = RTP_MIN_PORT_DEFAULT;
static int rtp_max_port = RTP_MAX_PORT_DEFAULT;
static int rtp_port;

static inline unsigned int hash_func_sess(const int table_size, void *data)
{
	rmd_session_t *sess = (rmd_session_t *)data;
	return hash_func_str(table_size, sess->sid);
}

static inline int cmp_func_sess(void *data, void *param)
{
	rmd_session_t *sess = (rmd_session_t *)data;
	return ds_cmp_str(sess->sid, param);
}

/* the last three parameters only for ELEC */
static int play_sess(driver_t *driver, device_t *device, channel_t *channel,
		char *stream_opt, char *stream_fmt, 
		char *plat, int	device_type, int device_id)
{
	realplay_info_t info;

	memset(&info, 0, sizeof(info));
	snprintf(info.ip, sizeof(info.ip), device->ip);
	info.port = device->port;
	snprintf(info.user, sizeof(info.user), device->user);
	snprintf(info.pwd, sizeof(info.pwd), device->pwd);
	info.channel_id = channel->id;
	snprintf(info.stream_opt, sizeof(info.stream_opt), stream_opt);
	snprintf(info.stream_fmt, sizeof(info.stream_fmt), stream_fmt);
	info.hdr_cb = rmd_data_callback_hdr;
	info.data_cb = rmd_data_callback_real;
	info.state_cb = realplay_state_callback;
	info.param = (void *)channel;
	info.is_rtp_packet = 0;
	info.payload_type = -1;

#ifdef RMD_ELEC_CONVERT		/* only for ELEC */
	snprintf(info.plat, sizeof(info.plat), plat);
	info.device_type = device_type;
	info.device_id = device_id;
#endif

	info.get_runtime = get_runtime;

	channel->realplay_handle = driver->rmd_di_start_realplay(&info);
	if (channel->realplay_handle == -1) {
		syslog(LOG_DEBUG, "realplay error[%s:%d]", info.ip, info.port);
		return -1;
	}
	channel->is_rtp_packet = info.is_rtp_packet;
	channel->payload_type = info.payload_type;
	channel->camera_state = 1;

	return 0;
}

static int clean_sess(rmd_session_t *sess)
{
	if (sess == NULL)
		return -1;

	if (sess->cli_rtp_sock) {
		if (sess->cli_rtp_sock->rtp_sock != -1)
			close(sess->cli_rtp_sock->rtp_sock);
		if (sess->rtcp_handle != -1)
			rmd_rtcp_stop_session(sess->rtcp_handle);
		if (sess->cli_rtp_sock->rtcp_sock != -1)
			close(sess->cli_rtp_sock->rtcp_sock);
		free(sess->cli_rtp_sock);
	}

	free(sess);
	return 0;
}

static inline int free_sess_node(void *data, void *param)
{
	return clean_sess((rmd_session_t *)data);
}

static inline int cmp_rtp_sock(void *a, void *b)
{
	cli_rtp_sock_t *p = (cli_rtp_sock_t *)a;
	return (p->rtp_sock == (int)b) ? 0 : -1;
}

static int dispatch_port(rmd_session_t *sess, char *cli_ip, int cli_rtp_port, 
		int cli_rtcp_port)
{
	int port;
	int sock[2];
	static int i = 0;

	while (1) {
		port = rtp_min_port + 2 * i++;
		sock[1] = udpsock(cli_ip, cli_rtp_port, 
				&sess->cli_rtp_sock->rtp_addr, port);
		sock[2] = udpsock(cli_ip, cli_rtcp_port, 
				&sess->cli_rtp_sock->rtcp_addr, port + 1);
		if (sock[1] == -1)
			close(sock[1]);
		if (sock[2] == -1)
			close(sock[2]);

		if (port >= rtp_max_port)
			i = 0;

		if (sock[1] != -1 && sock[2] != -1)
			break;
	}

	sess->cli_rtp_sock->rtp_sock = sock[1];
	sess->cli_rtp_sock->rtcp_sock = sock[2];
	return port;
}

static rmd_session_t *make_new_sess(rmd_session_t *info, 
		int cli_fd, char *cli_ip, int cli_rtp_port, 
		int cli_rtcp_port, int *svr_rtp_port)
{
	rmd_session_t *sess = NULL;

	sess = malloc(sizeof(rmd_session_t));
	if (sess == NULL)
		goto err;

	memcpy(sess, info, sizeof(rmd_session_t));
	sess->tcp_sock = cli_fd;
	sess->cli_rtp_sock = NULL;
	sess->rtcp_handle = -1;

	if (sess->trans_method == TRANS_VIA_UDP) {
		sess->cli_rtp_sock = malloc(sizeof(cli_rtp_sock_t));
		if (sess->cli_rtp_sock == NULL)
			goto err;
		sess->cli_rtp_sock->rtp_sock = -1;
		sess->cli_rtp_sock->rtcp_sock = -1;

		*svr_rtp_port = dispatch_port(sess, cli_ip, cli_rtp_port, 
				cli_rtcp_port);
		sess->rtcp_handle = rmd_rtcp_start_session(sess);
		if (sess->rtcp_handle == -1)
			goto err;
	}

	return sess;

err:
	clean_sess(sess);
	return NULL;
}

#ifdef RMD_DYNAMIC_DEVICES
static void remove_channel(rmd_session_t *s)
{
	int flag = 0;

	pthread_mutex_lock(&s->channel->mtx);
	if (s->channel->ref <= 0) {
		flag = 1;
		rmd_devmgr_remove_channel(s->driver, s->device, s->channel);
	}
	pthread_mutex_unlock(&s->channel->mtx);

	if (flag)
		rmd_devmgr_free_channel(s->channel);
}
#endif

int rmd_sessmgr_init()
{
	sess_table = hash_init(400, hash_func_sess);

	getcfg(cfg_file, "rtp_min_port", &rtp_min_port, GETCFG_INT32);
	getcfg(cfg_file, "rtp_max_port", &rtp_max_port, GETCFG_INT32);
	rtp_port = rtp_min_port;

	return 0;
}

int rmd_sessmgr_add(rmd_session_t *info, device_t *new_device, 
		int cli_fd, char *cli_ip, int cli_rtp_port, 
		int cli_rtcp_port, int *svr_rtp_port)
{
	rmd_session_t *sess = NULL;
	int ret = -1;

	if (info->trans_method != TRANS_VIA_TCP && 
			info->trans_method != TRANS_VIA_UDP) {
		syslog(LOG_DEBUG, "unknown trans method");
		return -1;
	}

	LOCK_SESS

#ifndef RMD_DYNAMIC_DEVICES
	if (rmd_devmgr_lookup_channel(info->driver_type, info->device_id, 
				info->channel_id, &info->driver, 
				&info->device, &info->channel) != 0) {
		syslog(LOG_DEBUG, "channel not exist");
		goto out;
	}
#else
	if (rmd_devmgr_lookup_channel_dynamic(info->driver_type, 
				info->device_id, info->channel_id, 
				&info->driver, &info->device, &info->channel, 
				new_device) != 0) {
		syslog(LOG_DEBUG, "add channel failed");
		goto out;
	}
#endif

	sess = make_new_sess(info, cli_fd, cli_ip, cli_rtp_port, 
			cli_rtcp_port, svr_rtp_port);
	if (sess == NULL) {
#ifdef RMD_DYNAMIC_DEVICES
		remove_channel(sess);
#endif
		goto out;
	}

	if (hash_add(sess_table, (void *)sess) != 0) {
#ifdef RMD_DYNAMIC_DEVICES
		remove_channel(sess);
#endif
		clean_sess(sess);
		goto out;
	}

	sess->channel->ref++;
	ret = 0;

out:
	UNLOCK_SESS
	return ret;
}

int rmd_sessmgr_play(const char *sid, play_succ_callback_t succ_cb, 
		void *param)
{
	int ret = -1;
	int make_key_frame = 1;

	LOCK_SESS

	rmd_session_t node;
	rmd_session_t *sess;
	driver_t *driver;
	device_t *device;
	channel_t *channel;

	snprintf(node.sid, sizeof(node.sid), sid);
	if (hash_entry(sess_table, (void *)&node, cmp_func_sess, 
				(void *)sid, (void **)&sess) == -1)
		goto unlock_sess_mtx;

	if (sess->sess_played == 1)	/* this session already played */
		goto unlock_sess_mtx;

	driver = sess->driver;
	device = sess->device;
	channel = sess->channel;

	pthread_mutex_lock(&channel->mtx);

#ifdef RMD_HAS_REC
	if (channel->rec == 1) {
		/* Note: If this channel not ready yet, jump over call 
		 * start_realplay() at here (because have another record 
		 * task will call start_realplay() until success).
		 */
		if (channel->camera_state == 0)
			goto unlock_cnl_mtx;
		goto direct_response;
	}
#endif

	if (SESSION_EMPTY(channel)) {
		char plat[32] = "";
		int device_type = 0;
		int device_id = 0;

#ifdef RMD_ELEC_CONVERT
		snprintf(plat, sizeof(plat), sess->plat);
		device_type = sess->device_type;

		if (sess->device_sub_id == 0)
			device_id = sess->device_id;
		else
			device_id = sess->device_sub_id;
#endif

		if (play_sess(driver, device, channel, sess->stream_opt, 
					sess->stream_fmt,
					plat, device_type, device_id) != 0)
			goto unlock_cnl_mtx;
		make_key_frame = 0;
	} else {
		if (channel->camera_state == 0)
			goto unlock_cnl_mtx;
	}

#ifdef RMD_HAS_REC
direct_response:
#endif
	/* send response */
	if (succ_cb)
		succ_cb(param);

	/* add socket infomation into channel's client list */
	if (sess->trans_method == TRANS_VIA_TCP) {
		if (dlist_add(&channel->tcp_clients, 
					(void *)sess->tcp_sock) == -1)
			goto unlock_cnl_mtx;
	} else {
		if (dlist_add(&channel->rtp_clients, sess->cli_rtp_sock) == -1)
			goto unlock_cnl_mtx;
	}

	if (make_key_frame == 1)
		driver->rmd_di_make_key_frame(channel->realplay_handle);

	rmd_event_report_session(EVENT_SESSION_START, 
			sess->user, device->id, channel->id,
			sess->tcp_sock, sid);

	sess->sess_played = 1;
	ret = 0;

	syslog(LOG_DEBUG, "[SESSION: PLAY]: %s", sid);

unlock_cnl_mtx:
	pthread_mutex_unlock(&channel->mtx);

unlock_sess_mtx:
	UNLOCK_SESS
	return ret;
}

int rmd_sessmgr_del(const char *sid)
{
	rmd_session_t node;
	rmd_session_t *sess;
	driver_t *driver;
	device_t *device;
	channel_t *channel;
	int tcp_sock;

	LOCK_SESS

	snprintf(node.sid, sizeof(node.sid), sid);
	if (hash_entry(sess_table, (void *)&node, cmp_func_sess, 
				(void *)sid, (void **)&sess) == -1)
		goto unlock_sess_mtx;
	driver = sess->driver;
	device = sess->device;
	channel = sess->channel;
	tcp_sock = sess->tcp_sock;

	pthread_mutex_lock(&channel->mtx);

	char user[USER_NAME_LEN];
	snprintf(user, sizeof(user), sess->user);
	int device_id = device->id;
	int channel_id = channel->id;

	if (sess->trans_method == TRANS_VIA_TCP) {
		dlist_del(&channel->tcp_clients, ds_cmp_val,
				(void *)sess->tcp_sock, 
				ds_none_callback, NULL);
	} else {
		dlist_del(&channel->rtp_clients, cmp_rtp_sock,
				(void *)sess->cli_rtp_sock->rtp_sock, 
				ds_none_callback, NULL);
	}

	if (SESSION_EMPTY(channel)) {
#ifdef RMD_HAS_REC
		/* never stop realplay on a record camera */
		if (channel->rec == 1)
			goto close_ptz_only;
#endif

		driver->rmd_di_stop_realplay(channel->realplay_handle);
		channel->realplay_handle = -1;
		channel->camera_state = 0;

#ifdef RMD_HAS_REC
close_ptz_only:
		;
#endif

#ifdef RMD_HAS_PTZ
		if (channel->ptz_loginid != -1) {
			close(channel->ptz_loginid);
			channel->ptz_loginid = -1;
		}
		if (channel->cam_loginid != -1) {
			close(channel->cam_loginid);
			channel->cam_loginid = -1;
		}
#endif
	}

	pthread_mutex_unlock(&channel->mtx);

	sess->channel->ref--;
#ifdef RMD_DYNAMIC_DEVICES
	remove_channel(sess);
#endif

	hash_del(sess_table, (void *)&node, cmp_func_sess, (void *)sid,
			free_sess_node, NULL);

	rmd_event_report_session(EVENT_SESSION_STOP,
			user, device_id, channel_id,
			tcp_sock, node.sid);

	syslog(LOG_DEBUG, "[SESSION: TEARDOWN]: %s", node.sid);

unlock_sess_mtx:
	UNLOCK_SESS
	return 0;
}

int rmd_sessmgr_is_valid_sid(const char *sid)
{
	int sidlen;

	sidlen = strlen(sid);
	if (sidlen == 0 || sidlen > RMD_SID_LEN)
		return -1;
	return 0;
}

#ifdef RMD_HAS_REC
int rmd_sessmgr_play_by_rec(channel_t *channel)
{
	char opt[16];
	int ret;

	if (channel->id != 0)
		snprintf(opt, sizeof(opt), STREAMOPT_MAIN);
	else
		snprintf(opt, sizeof(opt), STREAMOPT_SUB);

	pthread_mutex_lock(&channel->mtx);
	ret = play_sess(channel->pdriver, channel->pdevice, channel, 
			opt, STREAMFMT_H264, "", 0, 0);
	pthread_mutex_unlock(&channel->mtx);
	return ret;
}
#endif
