#ifndef _RMD_SESSMGR_H_
#define _RMD_SESSMGR_H_

#include <netinet/in.h>
#include "rmd_devmgr.h"

#define TRANS_VIA_TCP	1	/* transmit via tcp, e.g., RTSP */
#define TRANS_VIA_UDP	2	/* transmit via udp, e.g., SIP */
#define RMD_SID_LEN	128	/* session identifier max length */
#define USER_NAME_LEN	128

typedef struct {
	int	rtp_sock;
	struct	sockaddr_in rtp_addr;

	int	rtcp_sock;
	struct	sockaddr_in rtcp_addr;
} cli_rtp_sock_t;

/* rmd session infomation */
typedef struct {
	char 	sid[RMD_SID_LEN + 1];	/* session id */
	char	user[USER_NAME_LEN];	/* user name */
	int	trans_method;		/* TRANS_VIA_TCP or TRANS_VIA_UDP */

	int     tcp_sock;
	cli_rtp_sock_t *cli_rtp_sock;
	char	stream_opt[16];
	char	stream_fmt[16];
	int	sess_played;
	unsigned long rtcp_handle;

	/* ... */

	driver_t  *driver;
	device_t  *device;
	channel_t *channel;

	int	driver_type;
	int	device_id;
	int	channel_id;

#ifdef RMD_ELEC_CONVERT		/* only for ELEC */
	char	plat[32];
	int	device_type;
	int	device_sub_id;
#endif
} rmd_session_t;

/* initialize session table */
int rmd_sessmgr_init();

/* add a session into session table. RTSP:cli_fd>=0 SIP:cli_fd=-1 */
int rmd_sessmgr_add(rmd_session_t *info, device_t *new_device, 
		int cli_fd, char *cli_ip, int cli_rtp_port, 
		int cli_rtcp_port, int *svr_rtp_port);

/* start a session */
typedef int (*play_succ_callback_t)(void *param);
int rmd_sessmgr_play(const char *sid, play_succ_callback_t succ_cb, 
		void *param);

/* remove a session from session table */
int rmd_sessmgr_del(const char *sid);

/* judge the session ID is valid */
int rmd_sessmgr_is_valid_sid(const char *sid);

#ifdef RMD_HAS_REC
int rmd_sessmgr_play_by_rec(channel_t *channel);
#endif

#endif	/* _RMD_SESSMGR_H_ */
