#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "libmodel.h"
#include "single_login.h"
#include "base64_encode.h"

#define ENO			SDK_GetLastError()

static single_login_t *sl = NULL;

NORMAL_H264_SDP_CONTENT_FUNC

static void disconn_cb(LONG user_id, char *ip, LONG port, DWORD arg)
{
	printf("The ZXW Device(%s:%ld) disconnect!\n", ip, port);
}

static void reconn_cb(LONG user_id, char *ip, LONG port, DWORD arg)
{
}

static int login_dvr(char *ip, int port, char *user, char *pwd, void *param)
{
	int login_id = 0, err = 0;
	RVNetDeviceInfo dev_info = {0};

	login_id = SDK_Login(ip, port, user, pwd, &dev_info, &err, 0, NULL);
	if (login_id == 0) {
		syslog(LOG_DEBUG, "SDK_Login() error:%d", err);
		return -1;
	}
	syslog(LOG_DEBUG, "SDK_Login() success: %d", login_id);
	return login_id;
}

static int logout_dvr(void *data, void *param)
{
	int login_id = (int)param;
	if (SDK_Logout(login_id) == 0) {
		syslog(LOG_DEBUG, "SDK_Logout() error:%d", ENO);
		return -1;
	}
	syslog(LOG_DEBUG, "SDK_Logout() success: %d", login_id);
	return 0;
}

static void realdata_callback(LONG hdl, DWORD type, BYTE *buff, DWORD bytes, 
/*	LONG param,*/ DWORD arg)
{
	realplay_info_t *info = (realplay_info_t *)arg;

	syslog(LOG_DEBUG, "receive data type %d, size %d", type, bytes);
	if (info == NULL || info->data_cb == NULL)
		return;
//	if ( 0 == type)
		info->data_cb((unsigned long)info, (char *)buff, bytes, info->param);
//	static FILE *fpsave = NULL;
//	if( fpsave == NULL)
//		fpsave = fopen("./save.264", "w");
//	fwrite(buff, 1, bytes, fpsave);
}
/*
#define NOACT	10001
#define START	0
#define STOP	1
typedef struct {
	int ori_cmd;
	int dst_cmd;
	int stop;			// 0: start 1: stop /
} proto_table_t;

static proto_table_t proto_table[] = {
	{IRIS_CLOSE_STOP, 	DH_PTZ_APERTURE_DEC_CONTROL, 	STOP},
	{IRIS_CLOSE_START, 	DH_PTZ_APERTURE_DEC_CONTROL, 	START},
	{IRIS_OPEN_START, 	DH_PTZ_APERTURE_ADD_CONTROL,  	START},
	{IRIS_OPEN_STOP, 	DH_PTZ_APERTURE_ADD_CONTROL,  	STOP},
	{FOCUS_NEAR_STOP, 	DH_PTZ_FOCUS_ADD_CONTROL, 	STOP},
	{FOCUS_NEAR_START, 	DH_PTZ_FOCUS_ADD_CONTROL, 	START},
	{FOCUS_FAR_STOP, 	DH_PTZ_FOCUS_DEC_CONTROL,  	STOP},
	{FOCUS_FAR_START, 	DH_PTZ_FOCUS_DEC_CONTROL, 	START},
	{ZOOM_OUT_STOP, 	DH_PTZ_ZOOM_DEC_CONTROL,   	STOP},
	{ZOOM_OUT_START, 	DH_PTZ_ZOOM_DEC_CONTROL,   	START},
	{ZOOM_IN_STOP, 		DH_PTZ_ZOOM_ADD_CONTROL,    	STOP},
	{ZOOM_IN_START, 	DH_PTZ_ZOOM_ADD_CONTROL,    	START},
	{TILT_UP_STOP, 		DH_PTZ_UP_CONTROL,    		STOP},
	{TILT_UP_START, 	DH_PTZ_UP_CONTROL,    		START},
	{TILT_DOWN_STOP, 	DH_PTZ_DOWN_CONTROL,  		STOP},
	{TILT_DOWN_START, 	DH_PTZ_DOWN_CONTROL,  		START},
	{PAN_RIGHT_STOP, 	DH_PTZ_RIGHT_CONTROL,  		STOP},
	{PAN_RIGHT_START, 	DH_PTZ_RIGHT_CONTROL,  		START},
	{PAN_LEFT_STOP, 	DH_PTZ_LEFT_CONTROL,   		STOP},
	{PAN_LEFT_START, 	DH_PTZ_LEFT_CONTROL,   		START},
	{SET_PRESET_STOP, 	DH_PTZ_POINT_SET_CONTROL, 	STOP},
	{GOTO_PRESET_STOP, 	DH_PTZ_POINT_MOVE_CONTROL,	STOP},
	{CLE_PRESET_STOP, 	DH_PTZ_POINT_DEL_CONTROL, 	STOP},
	{UP_LEFT_STOP, 		DH_EXTPTZ_LEFTTOP,    		STOP},
	{UP_LEFT_START, 	DH_EXTPTZ_LEFTTOP,    		START},
	{DOWN_LEFT_STOP, 	DH_EXTPTZ_LEFTDOWN,  		STOP},
	{DOWN_LEFT_START, 	DH_EXTPTZ_LEFTDOWN,  		START},
	{UP_RIGHT_STOP, 	DH_EXTPTZ_RIGHTTOP,   		STOP},
	{UP_RIGHT_START, 	DH_EXTPTZ_RIGHTTOP,   		START},
	{DOWN_RIGHT_STOP, 	DH_EXTPTZ_RIGHTDOWN, 		STOP},
	{DOWN_RIGHT_START, 	DH_EXTPTZ_RIGHTDOWN, 		START},
	{CURR_ACTION_STOP, 	NOACT,      	STOP},	// stop current act /
	{WIPER_START, 		DH_PTZ_LAMP_CONTROL,		START},
	{WIPER_STOP, 		DH_PTZ_LAMP_CONTROL,		STOP},
	{LIGHT_START, 		DH_PTZ_LAMP_CONTROL,		START},
	{LIGHT_STOP, 		DH_PTZ_LAMP_CONTROL,		STOP},
	{HEATER_START, 		NOACT,				START},
	{HEATER_STOP, 		NOACT,				STOP},
	{INFRARED_START, 	NOACT,				STOP},
	{INFRARED_STOP, 	NOACT, 				STOP},
	{LINEAR_SCAN_START, 	DH_EXTPTZ_STARTLINESCAN, 	START},
	{LINEAR_SCAN_STOP, 	DH_EXTPTZ_STARTLINESCAN, 	STOP},
	{CRUISE_START, 		NOACT, 				START},
	{CRUISE_STOP, 		NOACT,				STOP},
	{SEQ_START, 		DH_EXTPTZ_RUNMODE, 		START},
	{SEQ_STOP, 		DH_EXTPTZ_STOPMODE, 		STOP},
	{PTZ_LOCK, 		NOACT, 				STOP},
	{PTZ_UNLOCK, 		NOACT, 				STOP}
};

static inline int protocol_trans(int *ctl_code, int *stop)
{
	int i;

	for (i = 0; i < sizeof(proto_table) / sizeof(proto_table_t); i++) {
		if (proto_table[i].ori_cmd != *ctl_code)
			continue;
		
		if (proto_table[i].dst_cmd == NOACT)
			return NOACT;

		*ctl_code = proto_table[i].dst_cmd;
		*stop = proto_table[i].stop;
		return 0;
	}

	return -1;
}

static int ptz_ctl(int login_id, int channel_id, ptz_ctl_info_t *info)
{
	int ret;
	int stop;

	ret = protocol_trans(&info->ctl_code, &stop);
	if (ret == NOACT)
		return 0;
	else if (ret == -1)
		return -1;

//	printf("%d %d %d %d %d\n", info->ctl_code, info->param1, 
//			info->param2, info->param3, stop);

	ret = SDK_DHPTZControl(login_id, channel_id - 1, info->ctl_code,
			info->param1, info->param2, info->param3, stop);
	return (ret == 1) ? 0 : -1;
}

*/
////////////////////////////////////////////////////////////////////////////
// special implementation
////////////////////////////////////////////////////////////////////////////

int special_init()
{
	SDK_Cleanup();
	if (SDK_Init(disconn_cb, 0) == 0)
		return -1;

	//SDK_SetAutoReconnect(reconn_cb, 0);
	SDK_SetConnectTime(10000, 1);

	sl = single_login_init();
	if (sl == NULL)
		return -1;

	return 0;
}

int special_uninit()
{
	SDK_Cleanup();
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
	int stream_opt;

	login_id = single_login(sl, login_dvr, info->ip, info->port, 
			info->user, info->pwd, NULL);
	if (login_id == -1)
		return -1;
	handle = (realplay_handle_t*)calloc(1, sizeof(realplay_handle_t));
	if (handle == NULL)
		goto err;
	memcpy(handle, info, sizeof(realplay_info_t));
	handle->login_id = login_id;

	if (strcmp(info->stream_opt, STREAMOPT_MAIN) == 0)
		stream_opt = RV_RType_Realplay_0;
	else
		stream_opt = RV_RType_Realplay_1;

	handle->realplay_handle = SDK_RealPlay(login_id, 
			info->channel_id - 1, NULL, (RV_RealPlayType)stream_opt, 0);
	if (handle->realplay_handle == 0) {
		syslog(LOG_DEBUG, "SDK_RealPlay error:%ld", ENO);
		goto err;
	}
	if (SDK_SetRealDataCallBack(handle->realplay_handle, 
				realdata_callback, (DWORD)handle/*, 0x0000001*/) == 0) {
		syslog(LOG_DEBUG, "SDK_SetRealDataCallBackEx() error:%ld", 
				ENO);
		goto err;
	}

	info->is_rtp_packet = 0;
	info->payload_type = -1;

	syslog(LOG_DEBUG, "start_realplay %s success", DEV_NAME);
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
	if (p == NULL || p->realplay_handle == -1)
		return -1;

	SDK_StopRealPlay(p->realplay_handle);
	single_logout(sl, logout_dvr, p->ip, p->port, (void *)p->login_id);
	free(p);
	p = NULL;

	syslog(LOG_DEBUG, "stop_realplay %s success", DEV_NAME);
	return 0;
}

int special_make_key_frame(unsigned long handle)
{
	return 0;
}
/*
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
*/
