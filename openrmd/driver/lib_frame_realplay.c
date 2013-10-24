#include "lib_frame_realplay.h"
#include "lib_special.h"

/* special implementation, normal in lib_special.c */
extern int special_init();
extern int special_uninit();
extern int special_get_describe(realplay_info_t *info, char **sdp);
extern unsigned long special_start_realplay(realplay_info_t *info);
extern int special_stop_realplay(unsigned long handle);
extern int special_apply_realdata(realplay_info_t *info);
extern int special_make_key_frame(unsigned long handle);
extern int special_ctl_ptz(int *login_id, unsigned long handle, 
		ptz_ctl_info_t *info);
extern int special_ctl_cam(int *login_id, unsigned long handle,
		ptz_ctl_info_t *info);

////////////////////////////////////////////////////////////////////////////
// driver interface
////////////////////////////////////////////////////////////////////////////

int rmd_di_get_info(int *type, int *hdr_len_max)
{
	if (type != NULL)
		*type = DEV_TYPE;
	if (hdr_len_max != NULL)
		*hdr_len_max = HDR_LEN_MAX;
	return 0;
}

int rmd_di_init()
{
	if (special_init() != 0)
		return -1;

	syslog(LOG_DEBUG, "type:%-2d name:%-9s ver:%-5.2f size:%-3d",
			DEV_TYPE, DEV_NAME, DEV_VER, HDR_LEN_MAX);
	return 0;
}

int rmd_di_uninit()
{
	special_uninit();
	return 0;
}

int rmd_di_get_describe(realplay_info_t *info, char **sdp)
{
	*sdp = NULL;
	return special_get_describe(info, sdp);
}

unsigned long rmd_di_start_realplay(realplay_info_t *info)
{
	info->media_hdr_sem = NULL;
	info->pkt_cb = NULL;	/* specify it in driver */
	return special_start_realplay(info);
}

int rmd_di_stop_realplay(unsigned long handle)
{
	if (handle == -1)
		return -1;
	return special_stop_realplay(handle);
}

int rmd_di_make_key_frame(unsigned long handle)
{
	if (handle == -1)
		return -1;
	return special_make_key_frame(handle);
}

int rmd_di_ctl_ptz(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return special_ctl_ptz(login_id, handle, info);
}

int rmd_di_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return special_ctl_cam(login_id, handle, info);
}
