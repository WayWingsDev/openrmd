#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "hsnnetsdk.h"

#define HSN_ENO			HSN_NET_GetLastError()

NORMAL_H264_SDP_CONTENT_FUNC

static void realdata_callback(LONG hdl, int type, char *buff, int bytes, 
	void *arg)
{
	realplay_info_t *info = (realplay_info_t *)arg;

	if (info == NULL || info->data_cb == NULL)
		return;
	info->data_cb((unsigned long)info, buff, bytes, info->param);
}

////////////////////////////////////////////////////////////////////////////
// special implementation
////////////////////////////////////////////////////////////////////////////

int special_init()
{
	if (HSN_NET_Init() == 0)
		return -1;
	return 0;
}

int special_uninit()
{
	HSN_NET_Cleanup();
	return 0;
}

int special_get_describe(realplay_info_t *info, char **sdp)
{
	return normal_h264_sdp_content(info, sdp, "", DEFAULT_FPS);
}

unsigned long special_start_realplay(realplay_info_t *info)
{
	realplay_handle_t *handle;
	int login_id;
	HSN_NET_REALPLAY real_info;

	login_id = HSN_NET_Login(info->ip, info->port, info->port, 
			info->user, info->pwd);
	if (login_id == -1) {
		syslog(LOG_DEBUG, "HSN_NET_Login() error:%d", HSN_ENO);
		return -1;
	}
	syslog(LOG_DEBUG, "HSN_NET_Login() success: %d", login_id);

	handle = calloc(1, sizeof(realplay_handle_t));
	if (handle == NULL)
		goto err;

	memcpy(handle, info, sizeof(realplay_info_t));
	handle->login_id = login_id;

	memset(&real_info, 0, sizeof(real_info));
	real_info.byType =  info->channel_id == 1 ? 0 : 1;
	real_info.byChannel = 0;
	real_info.byStatus = 1;
	real_info.byProtol = 1;

	handle->realplay_handle = HSN_NET_RealPlay(login_id, &real_info, 
			realdata_callback, handle);
	if (handle->realplay_handle == 0) {
		syslog(LOG_DEBUG, "HSN_NET_RealPlay error:%ld", HSN_ENO);
		goto err;
	}

	info->is_rtp_packet = 0;
	info->payload_type = -1;

	syslog(LOG_DEBUG, "start_realplay %s success", DEV_NAME);
	return (unsigned long)handle;

err:
	if (HSN_NET_Logout(login_id) == 0)
		syslog(LOG_DEBUG, "HSN_NET_Logout() success: %d", login_id);
	if (handle)
		free(handle);
	return -1;
}

int special_stop_realplay(unsigned long handle)
{
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (p == NULL || p->realplay_handle == -1)
		return -1;

	HSN_NET_StopRealPlay(p->realplay_handle);
	if (HSN_NET_Logout(p->login_id) == -1) {
		syslog(LOG_DEBUG, "HSN_NET_Logout() error:%d", HSN_ENO);
		return -1;
	}
	syslog(LOG_DEBUG, "HSN_NET_Logout() success: %d", p->login_id);
	free(p);
	p = NULL;

	syslog(LOG_DEBUG, "stop_realplay %s success", DEV_NAME);
	return 0;
}

int special_make_key_frame(unsigned long handle)
{
	return 0;
}

int special_ctl_ptz(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return -1;
}

int special_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return -1;
}
