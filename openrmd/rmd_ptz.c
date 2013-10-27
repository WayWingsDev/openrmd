#include "rmd.h"
#include "rmd_ptz.h"
#include "rmd_devmgr.h"

static inline int get_ptz_info(ptz_info_t *info, ptz_ctl_info_t *pi, 
		driver_t **driver, channel_t **channel, char *type)
{
	device_t *device;

	if (rmd_devmgr_lookup_channel(info->device_type, info->device_id,
			info->channel_id, driver, &device, channel) != 0)
		return -1;

	snprintf(pi->ip, sizeof(pi->ip), device->ip);
	pi->port = device->port;
	snprintf(pi->user, sizeof(pi->user), device->user);
	snprintf(pi->pwd, sizeof(pi->pwd), device->pwd);
	pi->ctl_code = info->ctl_code;
	pi->param1 = info->param1;
	pi->param2 = info->param2;
	pi->param3 = info->param3;
	pi->baud_rate = (*channel)->baud_rate;

<<<<<<< HEAD
	syslog(LOG_DEBUG, "[%s] dev:%d id:%d channel:%d code:0x%04X p1:%d p2:%d p3:%d\n", 
=======
	printf("[%s] dev:%d id:%d channel:%d code:0x%04X p1:%d p2:%d p3:%d\n", 
>>>>>>> 64d671fb5303708a1b14f1d09bf9a4c3f9b79e1c
			type,
			info->device_type, info->device_id, info->channel_id,
			info->ctl_code, info->param1, info->param2, 
			info->param3);
	return 0;
}

int rmd_ptz_ptz(ptz_info_t *info)
{
	driver_t *driver;
	channel_t *channel;
	ptz_ctl_info_t pi;

	if (get_ptz_info(info, &pi, &driver, &channel, "PTZ") != 0)
		return -1;

	return driver->rmd_di_ctl_ptz(&channel->ptz_loginid, 
			channel->realplay_handle, &pi);
}

int rmd_ptz_cam(ptz_info_t *info)
{
	driver_t *driver;
	channel_t *channel;
	ptz_ctl_info_t pi;

	if (get_ptz_info(info, &pi, &driver, &channel, "CAM") != 0)
		return -1;

	return driver->rmd_di_ctl_cam(&channel->cam_loginid, 
			channel->realplay_handle, &pi);
}
