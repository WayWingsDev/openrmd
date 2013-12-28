#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "rtspcli.h"

static const char *H264_URL_FMT = "rtsp://%s:%d/Realtime/%04d";

NORMAL_H264_SDP_CONTENT_FUNC

////////////////////////////////////////////////////////////////////////////
// special implementation
////////////////////////////////////////////////////////////////////////////

int special_init()
{
	return 0;
}

int special_uninit()
{
	return 0;
}

int special_get_describe(realplay_info_t *info, char **sdp)
{
	return normal_h264_sdp_content(info, sdp, "", DEFAULT_FPS);
}

unsigned long special_start_realplay(realplay_info_t *info)
{
	unsigned long handle;
	char url[512];

	info->is_rtp_packet = 1;
	snprintf(url, sizeof(url), H264_URL_FMT, 
			info->ip, info->port, info->channel_id);
	info->payload_type = RTP_PT_H264;

	handle = rtspcli_play(url, RTSP_TRANS_AVP, NULL, NULL, 
			info->data_cb, info->param, 0, info->get_runtime);
	if (handle == -1)
		return -1;

	syslog(LOG_DEBUG, "start_realplay %s success.", DEV_NAME);
	return handle;
}

int special_stop_realplay(unsigned long handle)
{
	rtspcli_stop(handle);
	syslog(LOG_DEBUG, "stop_realplay %s success.", DEV_NAME);
	return 0;
}

int special_make_key_frame(unsigned long handle)
{
	char content[] = "video: make_keyframe\r\n\r\n";
	return rtspcli_set_parameter(handle, content, strlen(content));
}

//////////////////////////////////////////////////////////////////////
// ptz control
int special_ctl_ptz(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return 0;
}

int special_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return 0;
}
