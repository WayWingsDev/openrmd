#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "hcnetsdk.h"
#include "single_login.h"
#include "base64_encode.h"

#define ENABLE_SUB_STREAM	0
#define HIK_ENO			NET_DVR_GetLastError()

static single_login_t *sl = NULL;
static int fps = 20;
unsigned long special_start_realplay(realplay_info_t *info);
int special_stop_realplay(unsigned long handle);

NORMAL_H264_SDP_CONTENT_FUNC

static int login_dvr(char *ip, int port, char *user, char *pwd, void *param)
{
	int login_id = NET_DVR_Login_V30(ip, port, user, pwd, (LPNET_DVR_DEVICEINFO_V30)param);
	if (login_id == -1) {
		syslog(LOG_DEBUG, "NET_DVR_Login_V30() error:%d", HIK_ENO);
		return -1;
	}
	syslog(LOG_DEBUG, "NET_DVR_Login_V30() success: %d", login_id);
	return login_id;
}

static int logout_dvr(void *data, void *param)
{
	int login_id = (int)param;
	if (NET_DVR_Logout_V30(login_id) == 0) {
		syslog(LOG_DEBUG, "NET_DVR_Logout_V30() error:%d", HIK_ENO);
		return -1;
	}
	syslog(LOG_DEBUG, "NET_DVR_Logout_V30() success: %d", login_id);
	return 0;
}

void CALLBACK realdata_callback(LONG hdl, DWORD type, BYTE *buff, DWORD bytes, 
		void *arg)
{
//	syslog(LOG_DEBUG, "Get data, the size is %d.\n)", bytes);

	realplay_info_t *info = (realplay_info_t *)arg;

	if (info == NULL)
		return;

	if (type == NET_DVR_SYSHEAD) {
		if (info->hdr_cb)
			info->hdr_cb((char *)buff, bytes, info->param);
		if (info->media_hdr_sem) {
			syslog(LOG_DEBUG, "media_hdr_sem %d", info->media_hdr_sem); 
			info->media_hdr_len = (bytes > HDR_LEN_MAX) ?
				HDR_LEN_MAX : bytes;
			memcpy(info->media_hdr, buff, info->media_hdr_len);
			sem_post(info->media_hdr_sem);
		}
		syslog(LOG_DEBUG, "receive sys head");
	} else if (info->data_cb) {
		info->data_cb((unsigned long)info, (char *)buff, bytes, 
				info->param);
	}
}

#define NOACT	10001
#define START	0
#define STOP	1
typedef struct {
	int ori_cmd;
	int dst_cmd;
	int stop;			/* 0: start 1: stop */
} proto_table_t;

static proto_table_t proto_table[] = {
	{IRIS_CLOSE_STOP, 	IRIS_CLOSE, 	STOP},
	{IRIS_CLOSE_START, 	IRIS_CLOSE, 	START},
	{IRIS_OPEN_START, 	IRIS_OPEN,  	START},
	{IRIS_OPEN_STOP, 	IRIS_OPEN,  	STOP},
	{FOCUS_NEAR_STOP, 	FOCUS_NEAR, 	STOP},
	{FOCUS_NEAR_START, 	FOCUS_NEAR, 	START},
	{FOCUS_FAR_STOP, 	FOCUS_FAR,  	STOP},
	{FOCUS_FAR_START, 	FOCUS_FAR, 	START},
	{ZOOM_OUT_STOP, 	ZOOM_OUT,   	STOP},
	{ZOOM_OUT_START, 	ZOOM_OUT,   	START},
	{ZOOM_IN_STOP, 		ZOOM_IN,    	STOP},
	{ZOOM_IN_START, 	ZOOM_IN,    	START},
	{TILT_UP_STOP, 		TILT_UP,    	STOP},
	{TILT_UP_START, 	TILT_UP,    	START},
	{TILT_DOWN_STOP, 	TILT_DOWN,  	STOP},
	{TILT_DOWN_START, 	TILT_DOWN,  	START},
	{PAN_RIGHT_STOP, 	PAN_RIGHT,  	STOP},
	{PAN_RIGHT_START, 	PAN_RIGHT,  	START},
	{PAN_LEFT_STOP, 	PAN_LEFT,   	STOP},
	{PAN_LEFT_START, 	PAN_LEFT,   	START},
	{SET_PRESET_STOP, 	SET_PRESET, 	STOP},	/* preset save */
	{GOTO_PRESET_STOP, 	GOTO_PRESET,	STOP},	/* preset call */
	{CLE_PRESET_STOP, 	CLE_PRESET, 	STOP},	/* preset delete */
	{UP_LEFT_STOP, 		UP_LEFT,    	STOP},
	{UP_LEFT_START, 	UP_LEFT,    	START},
	{DOWN_LEFT_STOP, 	DOWN_LEFT,  	STOP},
	{DOWN_LEFT_START, 	DOWN_LEFT,  	START},
	{UP_RIGHT_STOP, 	UP_RIGHT,   	STOP},
	{UP_RIGHT_START, 	UP_RIGHT,   	START},
	{DOWN_RIGHT_STOP, 	DOWN_RIGHT, 	STOP},
	{DOWN_RIGHT_START, 	DOWN_RIGHT, 	START},
	{CURR_ACTION_STOP, 	NOACT,      	STOP},	/* stop current act */
	{WIPER_START, 		WIPER_PWRON,	START},
	{WIPER_STOP, 		WIPER_PWRON,	STOP},
	{LIGHT_START, 		LIGHT_PWRON,	START},
	{LIGHT_STOP, 		LIGHT_PWRON,	STOP},
	{HEATER_START, 		HEATER_PWRON,	START},
	{HEATER_STOP, 		HEATER_PWRON,	STOP},
	{INFRARED_START, 	NOACT,		STOP},
	{INFRARED_STOP, 	NOACT, 		STOP},
	{LINEAR_SCAN_START, 	PAN_AUTO, 	START},
	{LINEAR_SCAN_STOP, 	PAN_AUTO, 	STOP},
	{CRUISE_START, 		RUN_CRUISE, 	START},
	{CRUISE_STOP, 		RUN_CRUISE,	STOP},
	{SEQ_START, 		RUN_SEQ, 	START},
	{SEQ_STOP, 		STOP_SEQ, 	STOP},
	{PTZ_LOCK, 		NOACT, 		STOP},
	{PTZ_UNLOCK, 		NOACT, 		STOP}
};

static inline int protocol_trans(int *ctl_code, int *stop, int *param1)
{
	int i;
	for (i = 0; i < sizeof(proto_table) / sizeof(proto_table_t); i++) {
		if (proto_table[i].ori_cmd != *ctl_code)
			continue;
		
		if (proto_table[i].dst_cmd == NOACT)
			return NOACT;

		*ctl_code = proto_table[i].dst_cmd;
		*stop = proto_table[i].stop;

		if (*ctl_code == SET_PRESET 
				|| *ctl_code == GOTO_PRESET
				|| *ctl_code == CLE_PRESET)
			return 0;

		if (*param1 < 1)
			*param1 = 1;
		else if (*param1 > 7)
			*param1 = 7;

		return 0;
	}

	return -1;
}

static int ptz_ctl(int login_id, int channel_id, ptz_ctl_info_t *info)
{
	int ret;
	int stop;

	ret = protocol_trans(&info->ctl_code, &stop, &info->param1);
	if (ret == NOACT)
		return 0;
	else if (ret == -1)
		return -1;

	if (info->ctl_code == SET_PRESET 
			|| info->ctl_code == GOTO_PRESET
			|| info->ctl_code == CLE_PRESET)
		return NET_DVR_PTZPreset_Other(login_id, channel_id,
				info->ctl_code, info->param1);

	syslog(LOG_DEBUG, "loginid:%d channel:%d ctlcode:%d stop:%d param1:%d\n", login_id, channel_id, info->ctl_code, stop, info->param1);
	return NET_DVR_PTZControlWithSpeed_Other(login_id, channel_id,
			info->ctl_code, stop, info->param1);
}

////////////////////////////////////////////////////////////////////////////
// special implementation
////////////////////////////////////////////////////////////////////////////

int special_init()
{
	if (NET_DVR_Init() == 0)
		return -1;

	sl = single_login_init();
	if (sl == NULL)
		return -1;

	return 0;
}

int special_uninit()
{
	NET_DVR_Cleanup();
	return 0;
}

int special_get_describe(realplay_info_t *info, char **sdp)
{
	unsigned long handle = -1;
	struct timespec ts;
	int ret = -1;
	char *sps = NULL;

	info->media_hdr = NULL;

	info->media_hdr_sem = (sem_t*)malloc(sizeof(sem_t));
	if (info->media_hdr_sem == NULL)
		goto out;
	if (sem_init(info->media_hdr_sem, 0, 0) == -1)
		goto out;

	info->media_hdr = (char*)calloc(HDR_LEN_MAX, sizeof(char));
	if (info->media_hdr == NULL)
		goto out;
	info->media_hdr_len = HDR_LEN_MAX;

	handle = special_start_realplay(info);
	if (handle == -1)
		goto out;

	ts.tv_nsec = 0;
	ts.tv_sec = time(NULL) + 3;
	SEM_TIMEDWAIT(info->media_hdr_sem, &ts, &ret);

out:
	syslog(LOG_DEBUG, "handle %d", handle);
	if (handle != -1)
		special_stop_realplay(handle);

	if (info->media_hdr_sem) {
		syslog(LOG_DEBUG, "media_hdr_sem %d", info->media_hdr_sem); 
		sem_destroy(info->media_hdr_sem);
		free(info->media_hdr_sem);
	}

	if (info->media_hdr) {
		syslog(LOG_DEBUG, "media_hdr: %s", info->media_hdr);
		if (ret != -1) {
			sps = base64_encode((uint8_t *)info->media_hdr, 
					info->media_hdr_len);
			if (sps == NULL)
				return -1;
		}
		free(info->media_hdr);
	}

	if (ret == -1)
		return -1;

	syslog(LOG_DEBUG, "media_hdr base64 encode: %s", sps); 
	normal_h264_sdp_content(info, sdp, sps, fps);
	free(sps);
	return 0;
}

unsigned long special_start_realplay(realplay_info_t *info)
{
	NET_DVR_CLIENTINFO cli_info = {0};
	//NET_DVR_PREVIEWINFO preview_info = {0};
	realplay_handle_t *handle;
	int login_id;

	login_id = single_login(sl, login_dvr, info->ip, info->port, 
			info->user, info->pwd, NULL);
	if (login_id == -1)
		return -1;
	handle = (realplay_handle_t*)calloc(1, sizeof(realplay_handle_t));
	if (handle == NULL)
		goto err;
	memcpy(handle, info, sizeof(realplay_info_t));
	handle->login_id = login_id;

	//syslog(LOG_DEBUG, "channel %d", info->channel_id);
	cli_info.lChannel = info->channel_id;
//	cli_info.lLinkMode = 0;		/* TCP */
	/*
	cli_info.hPlayWnd.x = 0;
	cli_info.hPlayWnd.y = 0;
	cli_info.hPlayWnd.uHeight = 0;
	cli_info.hPlayWnd.uWidth = 0;
	*/
//	cli_info.sMultiCastIP = NULL;
//	cli_info.hPlayWnd = 0;
/*
	preview_info.lChannel = info->channel_id;
	preview_info.dwStreamType = 0;
	preview_info.dwLinkMode = 0;
	preview_info.hPlayWnd = NULL;
	preview_info.bBlocked = 0;
	preview_info.byPreviewMode = 0;
	*/

#ifdef ENABLE_SUB_STREAM
//	if (strcmp(info->stream_opt, STREAMOPT_SUB) == 0) /* sub stream */
//		cli_info.lLinkMode |= 0x80000000;
#endif

	handle->realplay_handle = NET_DVR_RealPlay_V30(login_id, &cli_info, 
			realdata_callback, handle, 1);
//	handle->realplay_handle = NET_DVR_RealPlay_V40(login_id, &preview_info, 
//			realdata_callback, handle);
	syslog(LOG_DEBUG, "NET_DVR_RealPlay_V30 %d", HIK_ENO);
	if (handle->realplay_handle == -1) {
		syslog(LOG_DEBUG, "NET_DVR_RealPlay_V30 error:%d", HIK_ENO);
		goto err;
	}

	info->is_rtp_packet = 0;
	info->payload_type = -1;

	syslog(LOG_DEBUG, "start_realplay %s(%d %d) success", DEV_NAME, 
			info->channel_id, handle->realplay_handle);
	return (unsigned long)handle;

err:
	single_logout(sl, logout_dvr, info->ip, info->port, (void *)login_id);
	if (handle)
		free(handle);
	return -1;
}

int special_stop_realplay(unsigned long handle)
{
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (p->realplay_handle == -1 || p == NULL)
		return -1;

	int channel_id = p->channel_id;
	NET_DVR_StopRealPlay(p->realplay_handle);
	single_logout(sl, logout_dvr, p->ip, p->port, (void *)p->login_id);
	free(p);
	p = NULL;

	syslog(LOG_DEBUG, "stop_realplay %s(%d) success", DEV_NAME, channel_id);
	return 0;
}

int special_make_key_frame(unsigned long handle)
{
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (p->realplay_handle == -1 || p == NULL)
		return -1;

	NET_DVR_MakeKeyFrame(p->login_id, p->channel_id);
	return 0;
}

int special_ctl_ptz(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (handle == -1 || p == NULL)
		return -1;

	return ptz_ctl(p->login_id, p->channel_id, info);
}

int special_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (handle == -1 || p == NULL)
		return -1;

	return ptz_ctl(p->login_id, p->channel_id, info);
}
