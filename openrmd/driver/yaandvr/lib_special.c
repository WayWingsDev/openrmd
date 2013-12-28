#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "launet.h"

NORMAL_H264_SDP_CONTENT_FUNC

static void data_callback(unsigned long handle, int type, 
		char *buff, int bytes, void *param)
{
	realplay_info_t *info = (realplay_info_t *)param;

	if (info == NULL || info->data_cb == NULL)
		return;
	info->data_cb((unsigned long)info, buff, bytes, info->param);
}

#define NOACT	10001

typedef struct {
	int ori_cmd;
	int dst_cmd;
} proto_table_t;

static proto_table_t proto_table[] = {
	{IRIS_CLOSE_STOP, 	PTZ_IRISDECSTOP},
	{IRIS_CLOSE_START, 	PTZ_IRISDEC},
	{IRIS_OPEN_START, 	PTZ_IRISADD},
	{IRIS_OPEN_STOP, 	PTZ_IRISADDSTOP},
	{FOCUS_NEAR_STOP, 	PTZ_FOCUSDECSTOP},
	{FOCUS_NEAR_START, 	PTZ_FOCUSDEC},
	{FOCUS_FAR_STOP, 	PTZ_FOCUSADDSTOP},
	{FOCUS_FAR_START, 	PTZ_FOCUSADD},
	{ZOOM_OUT_STOP, 	PTZ_ZOOMDECSTOP},
	{ZOOM_OUT_START, 	PTZ_ZOOMDEC},
	{ZOOM_IN_STOP, 		PTZ_ZOOMADDSTOP},
	{ZOOM_IN_START, 	PTZ_ZOOMADD},
	{TILT_UP_STOP, 		PTZ_UPSTOP},
	{TILT_UP_START, 	PTZ_UP},
	{TILT_DOWN_STOP, 	PTZ_DOWNSTOP},
	{TILT_DOWN_START, 	PTZ_DOWN},
	{PAN_RIGHT_STOP, 	PTZ_RIGHTSTOP},
	{PAN_RIGHT_START, 	PTZ_RIGHT},
	{PAN_LEFT_STOP, 	PTZ_LEFTSTOP},
	{PAN_LEFT_START, 	PTZ_LEFT},
	{SET_PRESET_STOP, 	PTZ_SETPOINT},		/* preset save */
	{GOTO_PRESET_STOP, 	PTZ_GOTOPOINT},		/* preset call */
	{CLE_PRESET_STOP, 	PTZ_CLEARPOINT},	/* preset delete */
	{UP_LEFT_STOP, 		PTZ_LEFTUPSTOP},
	{UP_LEFT_START, 	PTZ_LEFTUP},
	{DOWN_LEFT_STOP, 	PTZ_LEFTDOWNSTOP},
	{DOWN_LEFT_START, 	PTZ_LEFTDOWN},
	{UP_RIGHT_STOP, 	PTZ_RIGHTUPSTOP},
	{UP_RIGHT_START, 	PTZ_RIGHTUP},
	{DOWN_RIGHT_STOP, 	PTZ_RIGHTDOWNSTOP},
	{DOWN_RIGHT_START, 	PTZ_RIGHTDOWN},
	{CURR_ACTION_STOP, 	PTZ_STOP},		/* stop current act */
	{WIPER_START, 		PTZ_RAIN},
	{WIPER_STOP, 		PTZ_RAINSTOP},
	{LIGHT_START, 		PTZ_LIGHT},
	{LIGHT_STOP, 		PTZ_LIGHTSTOP},
	{HEATER_START, 		NOACT},
	{HEATER_STOP, 		NOACT},
	{INFRARED_START, 	NOACT},
	{INFRARED_STOP, 	NOACT},
	{LINEAR_SCAN_START, 	NOACT},
	{LINEAR_SCAN_STOP, 	NOACT},
	{CRUISE_START, 		NOACT},
	{CRUISE_STOP, 		NOACT},
	{SEQ_START, 		NOACT},
	{SEQ_STOP, 		NOACT},
	{PTZ_LOCK, 		NOACT},
	{PTZ_UNLOCK, 		NOACT}
};

static inline int protocol_trans(int *ctl_code, int *param1)
{
	unsigned int i;

	for (i = 0; i < sizeof(proto_table) / sizeof(proto_table_t); i++) {
		if (proto_table[i].ori_cmd != *ctl_code)
			continue;
		
		if (proto_table[i].dst_cmd == NOACT)
			return NOACT;

		*ctl_code = proto_table[i].dst_cmd;

		if (*ctl_code == PTZ_SETPOINT 
				|| *ctl_code == PTZ_GOTOPOINT
				|| *ctl_code == PTZ_CLEARPOINT)
			return 0;

		if (*param1 < 1)
			*param1 = 1;
		else if (*param1 > 10)
			*param1 = 10;

		return 0;
	}

	return -1;
}

static int ptz_ctl(unsigned long handle, ptz_ctl_info_t *info)
{
	int ret;

	ret = protocol_trans(&info->ctl_code, &info->param1);
	if (ret == NOACT)
		return 0;
	else if (ret == -1)
		return -1;

	//printf("%d %d\n", info->ctl_code, info->param1);
	return VSNET_My_ClientPTZCtrl(handle, info->ctl_code, 
			info->param1);
}

////////////////////////////////////////////////////////////////////////////
// special implementation
////////////////////////////////////////////////////////////////////////////

int special_init()
{
	if (VSNET_My_SDK_Init() != TRUE)
		return -1;
	return 0;
}

int special_uninit()
{
	VSNET_My_SDK_Cleanup();
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

	pinfo->realplay_handle = VSNET_My_StartVideo(info->ip, info->port, 
			info->user, info->pwd, info->channel_id, 
			data_callback, pinfo);
	if (pinfo->realplay_handle == -1UL)
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

	VSNET_My_StopVideo(pinfo->realplay_handle);
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
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (handle == -1UL || p == NULL)
		return -1;
	return ptz_ctl(p->realplay_handle, info);
}

int special_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (handle == -1UL || p == NULL)
		return -1;
	return ptz_ctl(p->realplay_handle, info);
}
