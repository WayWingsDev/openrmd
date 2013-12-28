#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "rtspcli.h"

//static char *trans = RTSP_TRANS_UDP;
static char *trans = RTSP_TRANS_TCP;

static int fps = 20;
static const char *H264_URL_FMT = "rtsp://%s:%d/axis-media/media.amp"
"?videocodec=h264&audio=0&fps=%d&resolution=1920x1080";
static const char *H264_SMALL_URL_FMT = "rtsp://%s:%d/axis-media/media.amp"
"?videocodec=h264&audio=0&fps=%d&resolution=640x480";

#define BIG_SPS		"Z0IAKeKQDwBE/LgLcBAQHh4kRUA=,aM48gA=="
#define SMALL_SPS	"Z0IAKeKQFAX/LgLcBAQHh4kRUA==,aM48gA=="

NORMAL_H264_SDP_CONTENT_FUNC

static void sdp_callback(unsigned long handle, char *sdp, int sdp_bytes, 
		char *sps_encode, int sps_encode_bytes, 
		char *sps_decoded, int sps_decoded_bytes,
		void *param)
{
	if (sps_encode_bytes > RTSP_SPS_MAX)
		return;
	memcpy(param, sps_encode, sps_encode_bytes);
}

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
	/*
	unsigned long handle;
	char url[512], sps[RTSP_SPS_MAX + 1];

	memset(sps, 0, sizeof(sps));

	if (info->channel_id == 1) {
		snprintf(url, sizeof(url), H264_URL_FMT, info->ip, info->port,
				fps);
	} else if (info->channel_id == 2) {
		snprintf(url, sizeof(url), H264_SMALL_URL_FMT, info->ip, 
				info->port, fps);
	} else {
		syslog(LOG_DEBUG, "TODO: get audio data");
		return -1;
	}

	handle = rtspcli_play(url, trans, sdp_callback, sps,
			NULL, NULL, 0, NULL);
	if (handle == -1)
		return -1;

	rtspcli_stop(handle);
	return normal_h264_sdp_content(info, sdp, sps, fps);
	*/

	return normal_h264_sdp_content(info, sdp, 
			info->channel_id == 1 ? BIG_SPS : SMALL_SPS, fps);
}

unsigned long special_start_realplay(realplay_info_t *info)
{
	unsigned long handle;
	char url[512], sps[RTSP_SPS_MAX + 1];
	int sps_len;
	unsigned char sps_ext[] = {0x00, 0x00, 0x01, 0x41, 0x9B};
	int ext_len = sizeof(sps_ext);

	memset(sps, 0, sizeof(sps));
	info->is_rtp_packet = 1;

	if (info->channel_id == 1) {
		snprintf(url, sizeof(url), H264_URL_FMT, info->ip, info->port,
				fps);
		info->payload_type = RTP_PT_H264;
	} else if (info->channel_id == 2) {
		snprintf(url, sizeof(url), H264_SMALL_URL_FMT, info->ip, 
				info->port, fps);
		info->payload_type = RTP_PT_H264;
	} else {
		syslog(LOG_DEBUG, "TODO: get audio data");
		return -1;
	}
	
	handle = rtspcli_play(url, trans, sdp_callback, sps, 
			info->data_cb, info->param, 0, info->get_runtime);
	if (handle == -1)
		return -1;

	sps_len = strlen(sps);
	if (sps_len + ext_len > HDR_LEN_MAX) {
		rtspcli_stop(handle);
		return -1;
	}

	memcpy(&sps[sps_len], sps_ext, ext_len);
	info->hdr_cb(sps, sps_len + ext_len, info->param);
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
	return 0;
}

int special_ctl_ptz(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	printf("TODO\n");
	return 0;
}

int special_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	printf("TODO\n");
	return 0;
}
