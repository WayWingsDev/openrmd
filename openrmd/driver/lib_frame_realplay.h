#ifndef _LIB_FRAME_REALPLAY_H_
#define _LIB_FRAME_REALPLAY_H_

#include "syshdr.h"
#include "rmd_driver_interface.h"

#define CONN_TIMEOUT		3
#define RECV_TIMEOUT		20
#define RECONN_DELAY		5		/* re-connect delay(second) */
#define DEFAULT_FPS		25
#define SDP_MAX			2048		/* sdp max length */

/* PTZ control code */
#define IRIS_CLOSE_STOP		0x0101
#define IRIS_CLOSE_START	0x0102
#define IRIS_OPEN_START		0x0103
#define IRIS_OPEN_STOP		0x0104	
#define FOCUS_NEAR_STOP		0x0201
#define FOCUS_NEAR_START	0x0202
#define FOCUS_FAR_STOP		0x0203
#define FOCUS_FAR_START		0x0204
#define ZOOM_OUT_STOP		0x0301
#define ZOOM_OUT_START		0x0302
#define ZOOM_IN_STOP		0x0303
#define ZOOM_IN_START		0x0304
#define TILT_UP_STOP		0x0401
#define TILT_UP_START		0x0402
#define TILT_DOWN_STOP		0x0403
#define TILT_DOWN_START		0x0404
#define PAN_RIGHT_STOP		0x0501
#define PAN_RIGHT_START		0x0502
#define PAN_LEFT_STOP		0x0503
#define PAN_LEFT_START		0x0504
#define SET_PRESET_STOP		0x0601
#define GOTO_PRESET_STOP	0x0602
#define CLE_PRESET_STOP		0x0603
#define UP_LEFT_STOP		0x0701
#define UP_LEFT_START		0x0702
#define DOWN_LEFT_STOP		0x0703
#define DOWN_LEFT_START		0x0704
#define UP_RIGHT_STOP		0x0801
#define UP_RIGHT_START		0x0802
#define DOWN_RIGHT_STOP		0x0803
#define DOWN_RIGHT_START	0x0804
#define CURR_ACTION_STOP	0x0901
#define WIPER_START		0x0a01
#define WIPER_STOP		0x0a02
#define LIGHT_START		0x0b01
#define LIGHT_STOP		0x0b02
#define HEATER_START		0x0c01
#define HEATER_STOP		0x0c02
#define INFRARED_START		0x0d01
#define INFRARED_STOP		0x0d02
#define LINEAR_SCAN_START	0x0e01
#define LINEAR_SCAN_STOP	0x0e02
#define	CRUISE_START		0x0f01
#define	CRUISE_STOP		0x0f02
#define	SEQ_START		0x1001
#define	SEQ_STOP		0x1002
#define	PTZ_LOCK		0x1101
#define	PTZ_UNLOCK		0x1102

#define NORMAL_H264_SDP_CONTENT_FUNC \
static int normal_h264_sdp_content(realplay_info_t *info, char **sdp, \
		char *sps, int fps) \
{ \
	char *buff = (char *)malloc(SDP_MAX); \
	if (buff == NULL) \
		return -1; \
	\
	snprintf(buff, SDP_MAX, \
			"s=Mesia Presentation\r\n" \
			"e=NONE\r\n" \
			"b=AS:240000\r\n" \
			"t=0 0\r\n" \
			"a=control:*\r\n" \
			"a=range:npt=0.000000-\r\n" \
			"m=video %d RTP/AVP %d\r\n" \
			"a=framerate:%.1f\r\n" \
			"a=rtpmap:%d H264/90000\r\n" \
			"a=fmtp:%d packetization-mode=1;" \
			" profile-level-id=420033;" \
			" sprop-parameter-sets=%s\r\n" \
			"c=IN IP4 %s\r\n" \
			"\r\n", \
			info->svr_rtp_port, RTP_PT_H264, \
			(float)fps, \
			RTP_PT_H264, \
			RTP_PT_H264, \
			sps, \
			info->local_ip); \
	*sdp = buff; \
	return 0; \
}

#ifdef __cplusplus
extern "C" {
#endif

typedef realplay_info_t realplay_handle_t;

int rmd_di_init();
int rmd_di_uninit();
int rmd_di_get_info(int *type, int *hdr_len_max);
int rmd_di_get_describe(realplay_info_t *info, char **sdp);
unsigned long rmd_di_start_realplay(realplay_info_t *info);
int rmd_di_stop_realplay(unsigned long handle);
int rmd_di_make_key_frame(unsigned long handle);
int rmd_di_ctl_ptz(int *login_id, unsigned long handle, ptz_ctl_info_t *info);
int rmd_di_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info);

#ifdef __cplusplus
}
#endif
#endif	/* _LIB_FRAME_REALPLAY_H_ */
