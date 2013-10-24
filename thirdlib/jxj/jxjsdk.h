#include "HiSISDK.h"

#define JXJ_ERRNO	jxj_get_lasterr()

/* callback function prototype define */
typedef void (CALLBACK *jxj_exp_callback_t)(DWORD type, LONG user_id, 
		LONG handle, void *param);

typedef void (CALLBACK *jxj_realdata_callback_t)(LONG realplay_handle, 
		DWORD data_type, BYTE *buff, DWORD bytes, DWORD param);

/* interface function prototype define */
typedef BOOL  (WINAPI *jxj_sdk_init_t)();
typedef BOOL  (WINAPI *jxj_sdk_cleanup_t)();
typedef DWORD (WINAPI *jxj_get_lasterr_t)();
typedef DWORD (WINAPI *jxj_get_sdk_ver_t)();
typedef BOOL  (WINAPI *jxj_set_exp_callback_t)(jxj_exp_callback_t cbt, 
		void *param);
typedef LONG  (WINAPI *jxj_login_t)(char *ip, WORD dvr_port, WORD http_port, 
		char *user, char *pwd, HISI_DEVCEINFO *dev_info);
typedef BOOL  (WINAPI *jxj_logout_t)(LONG login_id);
typedef LONG  (WINAPI *jxj_realplay_t)(LONG login_id, 
		HISI_DEV_CLIENTINFO *real_info);
typedef BOOL  (WINAPI *jxj_stop_realplay_t)(LONG realplay_handle);
typedef BOOL  (WINAPI *jxj_open_sound_t)(LONG realplay_handle);
typedef BOOL  (WINAPI *jxj_close_sound_t)();
typedef BOOL  (WINAPI *jxj_set_realdata_callback_t)(LONG realplay_handle,
		jxj_realdata_callback_t cbk, DWORD param);
typedef BOOL  (WINAPI *jxj_ptz_ctl_t)(LONG realplay_handle, DWORD cmd, 
		DWORD stop);

/* interface function */
jxj_sdk_init_t		jxj_sdk_init;
jxj_sdk_cleanup_t	jxj_sdk_cleanup;
jxj_get_lasterr_t	jxj_get_lasterr;
jxj_get_sdk_ver_t	jxj_get_sdk_ver;
jxj_set_exp_callback_t	jxj_set_exp_callback;
jxj_login_t		jxj_login;
jxj_logout_t		jxj_logout;
jxj_realplay_t		jxj_realplay;
jxj_stop_realplay_t	jxj_stop_realplay;
jxj_open_sound_t	jxj_open_sound;
jxj_close_sound_t	jxj_close_sound;
jxj_set_realdata_callback_t jxj_set_realdata_callback;
jxj_ptz_ctl_t		jxj_ptz_ctl;

int jxj_load_library(char *dll_file)
{
	HMODULE dll;

	dll = LoadLibrary(dll_file);
	if (dll == NULL)
		return -1;

	if (!(jxj_sdk_init = (jxj_sdk_init_t)
			GetProcAddress(dll, "HISI_DVR_Init")) ||
		!(jxj_sdk_cleanup = (jxj_sdk_cleanup_t)
			GetProcAddress(dll, "HISI_DVR_Cleanup")) ||
		!(jxj_get_lasterr = (jxj_get_lasterr_t)
			GetProcAddress(dll, "HISI_DVR_GetLastError")) ||
		!(jxj_get_sdk_ver = (jxj_get_sdk_ver_t)
			GetProcAddress(dll, "HISI_DVR_GetSDKVersion")) || 
		!(jxj_set_exp_callback = (jxj_set_exp_callback_t)
			GetProcAddress(dll, "HISI_DVR_SetDVRMessage")) ||
		!(jxj_login = (jxj_login_t)
			GetProcAddress(dll, "HISI_DVR_Login")) ||
		!(jxj_logout = (jxj_logout_t)
			GetProcAddress(dll, "HISI_DVR_Logout")) ||
		!(jxj_realplay = (jxj_realplay_t)
			GetProcAddress(dll, "HISI_DVR_RealPlay")) ||
		!(jxj_stop_realplay = (jxj_stop_realplay_t)
			GetProcAddress(dll, "HISI_DVR_StopRealPlay")) ||
		!(jxj_open_sound = (jxj_open_sound_t)
			GetProcAddress(dll, "HISI_DVR_OpenSound")) ||
		!(jxj_close_sound = (jxj_close_sound_t)
			GetProcAddress(dll, "HISI_DVR_CloseSound")) ||
		!(jxj_set_realdata_callback =(jxj_set_realdata_callback_t)
			GetProcAddress(dll, "HISI_DVR_SetRealDataCallBack")) ||
		!(jxj_ptz_ctl = (jxj_ptz_ctl_t)
			GetProcAddress(dll, "HISI_DVR_PTZControl")))
			return -1;

	return 0;
}