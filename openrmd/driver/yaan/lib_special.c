#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "ynnetsdk.h"

NORMAL_H264_SDP_CONTENT_FUNC

static void data_callback(unsigned long handle, int type, 
		char *buff, int bytes, void *param)
{
	realplay_info_t *info = (realplay_info_t *)param;

	if (info == NULL || info->data_cb == NULL)
		return;
	info->data_cb((unsigned long)info, buff, bytes, info->param);
}

////////////////////////////////////////////////////////////////////////////
// special implementation
////////////////////////////////////////////////////////////////////////////

int special_init()
{
	YN_Init();
	return 0;
}

int special_uninit()
{
	return 0;
}

int special_get_describe(realplay_info_t *info, char **sdp)
{
	return normal_h264_sdp_content(info, sdp, (char *)"", DEFAULT_FPS);
}

unsigned long special_start_realplay(realplay_info_t *info)
{
	realplay_handle_t *pinfo = NULL;

	pinfo = (realplay_handle_t *)calloc(1, sizeof(realplay_handle_t));
	if (pinfo == NULL)
		goto err;
	memcpy(pinfo, info, sizeof(realplay_info_t));

	pinfo->realplay_handle = (unsigned long)YN_My_StartVideo(info->ip, 
			info->port, info->user, info->pwd, info->channel_id, 
			data_callback, pinfo);
	if (pinfo->realplay_handle == 0)
		goto err;

	syslog(LOG_DEBUG, "start_realplay %s success.", DEV_NAME);
	return (unsigned long)pinfo;

err:
	if (pinfo)
		free(pinfo);
	syslog(LOG_DEBUG, "start_realplay %s failed", DEV_NAME);
	return -1;
}

int special_stop_realplay(unsigned long handle)
{
	realplay_handle_t *pinfo = (realplay_handle_t *)handle;

	YN_My_StopVideo((YN_real_handle_t *)pinfo->realplay_handle);
	free(pinfo);
	syslog(LOG_DEBUG, "stop_realplay %s success", DEV_NAME);
	return 0;
}

int special_make_key_frame(unsigned long handle)
{
	return 0;
}

int special_ctl_ptz(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return 0;
}

int special_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return 0;
}
