#ifndef _DEVICE_CFG_H_
#define _DEVICE_CFG_H_

/* channel configure info */
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
} channel_cfg_t;

int add_line(char **buff, int *length, char *line);

int device_cfg_init();
int device_cfg_get(int old_ver, char **buff, int *length);
int device_cfg_cleanup();

char cfg_file[1024];

#endif	/* _DEVICE_CFG_H_ */
