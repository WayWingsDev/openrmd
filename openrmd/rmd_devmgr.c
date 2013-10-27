#include "rmd_devmgr.h"
#include "rmd.h"
#include "getcfg.h"
#include "getrpath.h"
#include "lookup_so.h"
#include "readbuf.h"
#include "hash.h"

#define DRIVER_TABLE_SIZE	100	/* default driver hash table size */

static hash_table_t *driver_table = NULL;	/* driver hash table */

/* device configure info */
typedef struct {
	int  type;
	int  id;
	char ip[32];
	int  port;
	char user[20];
	char pwd[20];
	int  channel_num;
	char rec[128];
	int  storage_device_type;
	char storage_ip[32];
	int  storage_port;
	char storage_user[20];
	char storage_pwd[20];
	int  storage_disk;
	int  baud_rate;
} device_cfg_t;

static inline unsigned int hash_func_driver(const int table_size, void *data)
{
	driver_t *p = (driver_t *)data;
	return (unsigned int)p->type % table_size;
}

static inline int cmp_func_driver(void *data, void *param)
{
	driver_t *p = (driver_t *)data;
	return (p->type == (int)param ? 0 : -1);
}

static inline int cmp_func_device(void *data, void *param)
{
	device_t *p = (device_t *)data;
	return (p->id == (int)param ? 0 : -1);
}

static inline int cmp_func_channel(void *data, void *param)
{
	channel_t *p = (channel_t *)data;
	return (p->id == (int)param ? 0 : -1);
}

static device_t *get_device(driver_t *driver, int id)
{
	device_t *device;

	if (dlist_entry(driver->devices, cmp_func_device, (void *)id, 
				(void **)&device) == -1) {
		//printf("no device: %d-%d\n", driver->type, id);
		return NULL;
	}
	return device;
}

static channel_t *get_channel(driver_t *driver, device_t *device, int id)
{
	channel_t *channel;

	if (dlist_entry(device->channels, cmp_func_channel, (void *)id, 
				(void **)&channel) == -1) {
		//printf("no channel: %d-%d-%d\n", 
		//		driver->type, device->id, id);
		return NULL;
	}
	return channel;
}

static channel_t *add_channel(device_cfg_t *cfg, int channel_id, int rec,
		driver_t *driver, device_t *device)
{
	channel_t *p;

	p = calloc(1, sizeof(channel_t));
	if (p == NULL)
		return NULL;

	pthread_mutex_init(&p->mtx, NULL);
	p->id = channel_id;
	p->ref = 0;
	p->realplay_handle = -1;

	if (driver->hdr_len_max > 0) {
		p->hdr_buff = malloc(driver->hdr_len_max);
		if (p->hdr_buff == NULL)
			goto err;
	} else {
		p->hdr_buff = NULL;
	}

	p->hdr_length = 0;  /* length not be sure until the header coming */

	p->tcp_clients = dlist_init();
	p->rtp_clients = dlist_init();

	p->is_rtp_packet = 0;
	p->payload_type = -1;
	p->camera_state = 0;

#ifdef RMD_HAS_REC
	p->rec = rec;
	p->storage_type = cfg->storage_device_type;
	p->rec_driver = NULL;
	p->pdriver = driver;
	p->pdevice = device;
	p->rec_state = 0;
	snprintf(p->storage_ip, sizeof(p->storage_ip), cfg->storage_ip);
	p->storage_port = cfg->storage_port;
	snprintf(p->storage_user, sizeof(p->storage_user), cfg->storage_user);
	snprintf(p->storage_pwd, sizeof(p->storage_pwd), cfg->storage_pwd);
	p->storage_disk = cfg->storage_disk;
#endif

#ifdef RMD_HAS_PTZ
	p->baud_rate = cfg->baud_rate;
	p->ptz_loginid = -1;
	p->cam_loginid = -1;
#endif

	if (dlist_add(&device->channels, (void *)p) == -1)
		goto err;

	//printf("add channel: %d-%d-%d\n", driver->type, device->id, p->id);
	return p;

err:
	if (p->hdr_buff)
		free(p->hdr_buff);
	pthread_mutex_destroy(&p->mtx);

	free(p);
	return NULL;
}

#ifndef RMD_DYNAMIC_DEVICES
static int add_channels(device_cfg_t *cfg, driver_t *driver, device_t *device)
{
	int i;
	int rec;

	if (cfg->channel_num <= 0 || cfg->channel_num > sizeof(cfg->rec))
		return -1;

	for (i = cfg->channel_num; i > 0; i--) {
		rec = (cfg->rec[i-1] == '1' ? 1 : 0);
		add_channel(cfg, i, rec, driver, device);
	}

	return 0;
}
#endif

static device_t *add_device(device_cfg_t *cfg, driver_t *driver)
{
	device_t *p;

	p = calloc(1, sizeof(device_t));
	if (p == NULL)
		return NULL;
	p->id = cfg->id;
	snprintf(p->ip, sizeof(p->ip), cfg->ip);
	p->port = cfg->port;
	snprintf(p->user, sizeof(p->user), cfg->user);
	snprintf(p->pwd, sizeof(p->pwd), cfg->pwd);
	p->channels = dlist_init();

	if (dlist_add(&driver->devices, (void *)p) == -1) {
		free(p);
		return NULL;
	}

	//printf("add device: %d-%d\n", driver->type, p->id);
	return p;
}

#ifndef RMD_DYNAMIC_DEVICES
static int add_devices()
{
	FILE *fp;
	char file[PATH_MAX], name[128], path[PATH_MAX], line[PATH_MAX];
	driver_t *driver;
	device_t *device;

	if (getcfg(cfg_file, "device_cfg_file", name, GETCFG_STR) != 0) {
		syslog(LOG_INFO, "can't get device cfg file info");
		return -1;
	}

	if (getrpath(path, sizeof(path)) == -1)
		snprintf(path, sizeof(path), ".");
	snprintf(file, sizeof(file), "%s/%s", path, name);

	if ((fp = fopen(file, "r")) == NULL)
		return -1;

	device_cfg_t cfg;
	int n;
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (line[0] == '#' || line[0] == '/' || strlen(line) == 1)
			continue;

		n = sscanf(line, "%d;%d;%[^;];%d;%[^;];%[^;];%d;%[^;];"
				"%d;%[^;];%d;%[^;];%[^;];%d;%d;",
				&cfg.type,
				&cfg.id,
				cfg.ip,
				&cfg.port,
				cfg.user,
				cfg.pwd,
				&cfg.channel_num,
				cfg.rec,
				&cfg.storage_device_type,
				cfg.storage_ip,
				&cfg.storage_port,
				cfg.storage_user,
				cfg.storage_pwd,
				&cfg.storage_disk,
				&cfg.baud_rate);
		if (n != 15)
			continue;

		driver = rmd_devmgr_get_driver(cfg.type);
		if (driver == NULL)
			continue;

		device = add_device(&cfg, driver);
		if (device == NULL)
			continue;
		add_channels(&cfg, driver, device);
	}
	fclose(fp);
	return 0;
}
#endif

static int add_driver(char *so)
{
	driver_t *driver;
	void *handle;

	handle = dlopen(so, RTLD_LAZY);
	if (handle == NULL) {
		syslog(LOG_DEBUG, "%s", dlerror());
		return -1;
	}

	driver = calloc(1, sizeof(driver_t));
	if (driver == NULL)
		goto err;

	if (!(driver->rmd_di_init = dlsym(handle, "rmd_di_init"))
			|| !(driver->rmd_di_uninit = 
				dlsym(handle, "rmd_di_uninit"))
			|| !(driver->rmd_di_get_info = 
				dlsym(handle, "rmd_di_get_info"))
			|| !(driver->rmd_di_get_describe = 
				dlsym(handle, "rmd_di_get_describe"))
			|| !(driver->rmd_di_start_realplay = 
				dlsym(handle, "rmd_di_start_realplay"))
			|| !(driver->rmd_di_stop_realplay = 
				dlsym(handle, "rmd_di_stop_realplay"))
			|| !(driver->rmd_di_make_key_frame = 
				dlsym(handle, "rmd_di_make_key_frame"))
#ifdef RMD_HAS_PTZ
			|| !(driver->rmd_di_ctl_ptz = 
				dlsym(handle, "rmd_di_ctl_ptz"))
			|| !(driver->rmd_di_ctl_cam = 
				dlsym(handle, "rmd_di_ctl_cam"))
#endif
			/* ... */)
		goto err;

	driver->devices = dlist_init();
	if (driver->rmd_di_get_info(&driver->type, &driver->hdr_len_max) != 0)
		goto err;
	if (driver->rmd_di_init() != 0)
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

static int add_drivers()
{
	int size;
	int n = 0;

	/* initialize hash table */
	if (getcfg(cfg_file, "device_driver_table_size", &size, 
				GETCFG_INT32) != 0)
		size = DRIVER_TABLE_SIZE;
	driver_table = hash_init(size, hash_func_driver);
	if (driver_table == NULL)
		return -1;

	/* load device drivers into hash table */
	char path[PATH_MAX], prefix[32];
	getcfg(cfg_file, "device_lib_path", path, GETCFG_STR);
	getcfg(cfg_file, "device_lib_name_prefix", prefix, GETCFG_STR);

	char *names = lookup_so(path, prefix);
	if (names == NULL) {
		syslog(LOG_ERR, "nono driver found");
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

int rmd_devmgr_init()
{
	int ret;

	ret = add_drivers();
	if (ret != 0)
		return -1;

#ifndef RMD_DYNAMIC_DEVICES
	add_devices();		/* get devices info from config file */
#else
	syslog(LOG_INFO, "dynamic devices");
#endif

	return 0;
}

int rmd_devmgr_lookup_channel(int driver_type, int device_id, int channel_id,
		driver_t **driver, device_t **device, channel_t **channel)
{
	*driver = rmd_devmgr_get_driver(driver_type);
	if (*driver == NULL)
	{
		syslog(LOG_DEBUG, "driver not found");
		return -1;
	}

	*device = get_device(*driver, device_id);
	if (*device == NULL)
	{
		syslog(LOG_DEBUG, "device:%d not found", device_id);
		return -1;
	}

	*channel = get_channel(*driver, *device, channel_id);
	if (*channel == NULL)
	{
		syslog(LOG_DEBUG, "channel:%d not found", channel_id);
		return -1;
	}

	return 0;
}

int rmd_devmgr_lookup_channel_dynamic(int driver_type, int device_id, 
		int channel_id, driver_t **driver, device_t **device, 
		channel_t **channel, device_t *new)
{
	//printf("lockup type:%d id:%d channel:%d\n", 
	//		driver_type, device_id, channel_id);

	device_cfg_t cfg;

	memset(&cfg, 0, sizeof(device_cfg_t));
	cfg.type = driver_type;
	cfg.id = device_id;
	snprintf(cfg.ip, sizeof(cfg.ip), new->ip);
	cfg.port = new->port;
	snprintf(cfg.user, sizeof(cfg.user), new->user);
	snprintf(cfg.pwd, sizeof(cfg.pwd), new->pwd);
	cfg.channel_num = 0;

	*driver = rmd_devmgr_get_driver(driver_type);
	if (*driver == NULL)
		return -1;

	*device = get_device(*driver, device_id);
	if (*device == NULL) {
		*device = add_device(&cfg, *driver);
		if (*device == NULL)
			return -1;
		*channel = add_channel(&cfg, channel_id, 0, *driver, *device);
		if (*channel == NULL)
			return -1;
		return 0;
	}

	*channel = get_channel(*driver, *device, channel_id);
	if (*channel == NULL) {
		*channel = add_channel(&cfg, channel_id, 0, *driver, *device);
		if (*channel == NULL)
			return -1;
	}
	return 0;
}

int rmd_devmgr_remove_channel(driver_t *driver, device_t *device, 
		channel_t *channel)
{

	if (dlist_del(&device->channels, cmp_func_channel, 
				(void *)channel->id, 
				ds_none_callback, NULL) == -1)
		return -1;
	//printf("remove channel: %d-%d-%d\n", 
	//		driver->type, device->id, channel->id);

	if (device->channels == NULL) {
	//	printf("remove device: %d-%d\n", driver->type, device->id);
		dlist_del(&driver->devices, cmp_func_device, 
				(void *)device->id, ds_free_callback, NULL);
	}

	return 0;
}

int rmd_devmgr_free_channel(channel_t *p)
{
	if (p == NULL)
		return -1;

	if (p->hdr_buff)
		free(p->hdr_buff);
	pthread_mutex_destroy(&p->mtx);
	free(p);
	return 0;
}

driver_t *rmd_devmgr_get_driver(int type)
{
	driver_t *driver, node;

	node.type = type;
	if (hash_entry(driver_table, (void *)&node, cmp_func_driver, 
				(void *)type, (void **)&driver) == -1) {
		//printf("no driver: %d\n", type);
		return NULL;
	}
	return driver;
}

static int travel_device_callback(void *data, void *param)
{
	device_t *device = (device_t *)data;

	dlist_for_each(device->channels, (travel_callback_t)param, NULL);
	return 0;
}

static int travel_driver_callback(void *data, void *param)
{
	driver_t *driver = (driver_t *)data;

	dlist_for_each(driver->devices, travel_device_callback, param);
	return 0;
}

int rmd_devmgr_travel_channel(travel_callback_t cb, void *param)
{
	hash_for_each(driver_table, travel_driver_callback, (void *)cb);
	return 0;
}
