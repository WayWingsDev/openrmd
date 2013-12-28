#ifndef _RTSPSVR_H_
#define _RTSPSVR_H_

#include "rtsp.h"

/* the type of rtspsvr callback function's parameter */
typedef struct {
	int  client_fd;
	char svrip[32];
	char cliip[32];
	char url[RTSP_URL_LEN];
	char *sdp;
	char trans[16];
	char cast[16];
	int  cli_rtp_port;
	int  cli_rtcp_port;
	int  svr_rtp_port;
	char sid[RTSP_SID_LEN + 1];	/* session id */
} rtspsvr_cbp_t;

/* let application layer can send respone when PLAY success. */
typedef int (*rtspsvr_play_succ_callback_t)(void *param);

/* rtsp server callback function typedef */
typedef int (*rtspsvr_describe_callback_t)(rtspsvr_cbp_t *cbp);
typedef int (*rtspsvr_setup_callback_t)(rtspsvr_cbp_t *cbp);
typedef int (*rtspsvr_play_callback_t)(char *sid, 
		rtspsvr_play_succ_callback_t reply_cb, void *param);
typedef int (*rtspsvr_pause_callback_t)(char *sid);
typedef int (*rtspsvr_teardown_callback_t)(char *sid);

typedef struct {
	rtspsvr_describe_callback_t	describe;
	rtspsvr_setup_callback_t	setup;
	rtspsvr_play_callback_t		play;
	rtspsvr_pause_callback_t	pause;
	rtspsvr_teardown_callback_t	teardown;
} rtspsvr_callback_t;

int rtspsvr_start(int lsnport, int max_clients, rtspsvr_callback_t *cb);
int rtspsvr_stop();

#endif	/* _RTSPSVR_H_ */
