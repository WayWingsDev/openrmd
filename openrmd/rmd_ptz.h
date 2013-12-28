#ifndef _RMD_PTZ_H_
#define _RMD_PTZ_H_

/* ptz command info */
typedef struct {
	int  device_type;
	int  device_id;
	int  channel_id;
	int  ctl_code;
	int  param1;
	int  param2;
	int  param3;
} ptz_info_t;

int rmd_ptz_ptz(ptz_info_t *info);
int rmd_ptz_cam(ptz_info_t *info);

#endif	/* _RMD_PTZ_H_ */
