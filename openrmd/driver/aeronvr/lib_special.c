#include "lib_special.h"
#include "lib_frame_rec.h"
#include "aeronvr.h"

static void msg_callback(unsigned int playtask, void *user, int err)
{
}

////////////////////////////////////////////////////////////////////////////
// special implementation
////////////////////////////////////////////////////////////////////////////

unsigned long special_geterror()
{
	return AVS_getLastError();
}

int special_init()
{
#ifdef NONE_BLOCKING
	char msg[] = "NONE BLOCKING";
#else
	char msg[] = "BLOCKING";
#endif
	syslog(LOG_DEBUG, "type:%-2d name:%-8s ver:%-4.2f %s",
			DEV_TYPE, DEV_NAME, DEV_VER, msg);
	return 0;
}

int special_login(char *ip, int port, char *user, char *pwd)
{
	return AVS_login(ip, port, user, pwd, msg_callback, NULL);
}

int special_logout(int login_id)
{
	return AVS_logout(login_id);
}

unsigned long special_start_record(start_record_info_t *info)
{
	unsigned long handle;

	handle = AVS_startRecord(info->login_id, info->record_name, 
			info->record_alias, info->record_type, 
			info->disk_no, info->hdr_buff, info->hdr_len, 
			info->desc, strlen(info->desc));
#ifdef NONE_BLOCKING
	return nb_start_record(handle, (record_callback_t)AVS_record, 
			(stop_record_callback_t)AVS_stopRecord);
#else
	return handle;
#endif
}

int special_record(unsigned long record_handle, char *buff, int bytes, 
		unsigned int bgn_time, unsigned int end_time)
{
#ifdef NONE_BLOCKING
	return nb_record(record_handle, buff, bytes, bgn_time, end_time);
#else
	return AVS_record(record_handle, buff, bytes, bgn_time, end_time);
#endif
}

int special_stop_record(unsigned long record_handle)
{
#ifdef NONE_BLOCKING
	return nb_stop_record(record_handle);
#else
	return AVS_stopRecord(record_handle);
#endif
}
