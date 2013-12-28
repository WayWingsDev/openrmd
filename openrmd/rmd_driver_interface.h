#ifndef _RMD_DRIVER_INTERFACE_H_
#define _RMD_DRIVER_INTERFACE_H_

#include "syshdr.h"
#include "rtp.h"

#define FRAME_SIZE	(1024 * 200)	/* frame buffer size */

/* stream option */
#define STREAMOPT_MAIN		"main"	/* main stream */
#define STREAMOPT_SUB		"sub"	/* sub stream */

/* stream format */
#define STREAMFMT_H264		"h264"	/* H.264 */
#define STREAMFMT_MJPEG		"mjpeg"	/* motion jpeg */

/* callback functions typedef */
typedef void (*realplay_hdr_callback_t)(char *buff, int bytes, void *param);
typedef void (*realplay_data_callback_t)(unsigned long handle, char *buff, 
		int bytes, void *param);
typedef void (*realplay_state_callback_t)(int state, void *param);

#include <time.h>
typedef time_t (*get_runtime_t)();

/* realplay info */
typedef struct {
	char	ip[32];
	int	port;
	char	user[20];
	char	pwd[20];

	int	channel_id;
	char	stream_opt[16];
	char	stream_fmt[16];

	unsigned long realplay_handle;	/* use for DVR */
	realplay_hdr_callback_t hdr_cb;
	realplay_data_callback_t data_cb;
	realplay_state_callback_t state_cb;
	void	*param;
	int	login_id;
	pthread_mutex_t login_id_mtx;
	int	is_rtp_packet;	/* 0: not rtp packet 1: rtp packet */
	int	payload_type;
	rtp_packetization_callback_t pkt_cb;

	/* the following three member only for DVR device */
	sem_t	*media_hdr_sem;
	char	*media_hdr;
	int	media_hdr_len;

	int	svr_rtp_port;
	char	local_ip[32];

#ifdef RMD_ELEC_CONVERT		/* only for ELEC */
	char	plat[32];
	int	device_type;
	int	device_id;
#endif

	get_runtime_t get_runtime;

	int (*fp_realplay_start)(void *info);
	int (*fp_realplay_stop)(void *info);
	sem_t play_sem;
	sem_t stop_sem;
	int play_ret;
	int stop_sess;
	pthread_t play_tid;
} realplay_info_t;

/* ptz control info */
typedef struct {
	char	ip[32];
	int	port;
	char	user[20];
	char	pwd[20];

	int	ctl_code;
	int	param1;
	int	param2;
	int	param3;
	int	baud_rate;
} ptz_ctl_info_t;

/* start record info */
typedef struct {
	int	login_id;
	char 	record_name[128];
	char	record_alias[128];
	int	record_type;
	int	disk_no;
	char 	hdr_buff[256];
	int 	hdr_len;
	char 	desc[256];
} start_record_info_t;

typedef int (*rmd_di_init_t)();
typedef int (*rmd_di_uninit_t)();
typedef int (*rmd_di_get_info_t)(int *type, int *hdr_len_max);

/* if success and *sdp != NULL, you need to free sdp's memory by youself. */
typedef int (*rmd_di_get_describe_t)(realplay_info_t *info, char **sdp);
typedef unsigned long (*rmd_di_start_realplay_t)(realplay_info_t *info);
typedef int (*rmd_di_stop_realplay_t)(unsigned long handle);
typedef int (*rmd_di_make_key_frame_t)(unsigned long handle);

#ifdef RMD_HAS_PTZ
typedef int (*rmd_di_ctl_ptz_t)(int *login_id, unsigned long realplay_handle,
		ptz_ctl_info_t *info);
typedef int (*rmd_di_ctl_cam_t)(int *login_id, unsigned long realplay_handle,
		ptz_ctl_info_t *info);
#endif

#ifdef RMD_HAS_REC
typedef int (*rmd_di_rec_init_t)(get_runtime_t get_runtime);
typedef int (*rmd_di_rec_get_info_t)(int *device_type);
typedef unsigned long (*rmd_di_rec_geterror_t)();
typedef int (*rmd_di_rec_login_t)(char *ip, int port, char *user, char *pwd);
typedef int (*rmd_di_rec_logout_t)(int login_id);
typedef unsigned long (*rmd_di_rec_start_record_t)(start_record_info_t *info);
typedef int (*rmd_di_rec_record_t)(unsigned long record_handle, char *buff, 
		int bytes, unsigned int bgn_time, unsigned int end_time);
typedef int (*rmd_di_rec_stop_record_t)(unsigned long record_handle);
#endif

#endif	/* _RMD_DRIVER_INTERFACE_H_ */
