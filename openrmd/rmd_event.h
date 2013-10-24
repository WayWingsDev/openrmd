#ifndef _RMD_EVENT_H_
#define _RMD_EVENT_H_

#include "rmd_sessmgr.h"

#define EVENT_PTZCONTROL		"Control_Camera"
#define EVENT_SESSION_START		"MediaPlay"
#define EVENT_SESSION_STOP		"MediaTeardown"
#define EVENT_GET_SESSION_LIST		"GetMediaPlayer"
#define EVENT_RESET_SESSION_LIST	"ResetMediaPlayer"

void rmd_event_report_session(char *event, 
		char *user, int device_id, int channel_id,
		int tcp_sock, const char *sid);

void rmd_event_trigger_hangup(rmd_session_t *sess);

void rmd_event_message_incoming(int msg_from_sip_thread, const char *msg_body);

void rmd_event_reset_sesslst_msgbody(char *buff, int buff_size);

#endif	/* _RMD_EVENT_H_ */
