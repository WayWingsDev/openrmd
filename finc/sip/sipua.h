#ifndef _SIPUA_H_
#define _SIPUA_H_

#include <pjsua-lib/pjsua.h>

/* typedef re-define */
#define sipua_reg_info		pjsua_reg_info
#define sipua_acc_id		pjsua_acc_id
#define sipua_call_id		pjsua_call_id
#define sipua_event		pjsip_event
#define sipua_rx_data		pjsip_rx_data
#define sipua_str_t		pj_str_t
#define sipua_msg_data		pjsua_msg_data
#define sipua_status_t		pj_status_t
#define sipua_thread_desc	pj_thread_desc
#define sipua_thread_t		pj_thread_t
#define sipua_rdata_sdp_info	pjsip_rdata_sdp_info

/* function re-define */
#define sipua_call_info		pjsua_call_info
#define sipua_call_get_info	pjsua_call_get_info
#define sipua_call_answer	pjsua_call_answer
#define sipua_call_hangup	pjsua_call_hangup
#define sipua_msg_data_init	pjsua_msg_data_init
#define sipua_str		pj_str
#define sipua_rdata_get_sdp_info pjsip_rdata_get_sdp_info

typedef struct {
	void (*on_reg_state)(sipua_acc_id acc_id, sipua_reg_info *info);
	void (*on_incoming_call)(sipua_acc_id acc_id, sipua_call_id call_id,
			sipua_rx_data *rdata);
	void (*on_call_state)(sipua_call_id call_id, sipua_event *e);
	void (*on_pager)(sipua_call_id call_id, const sipua_str_t *from,
			const sipua_str_t *to, const sipua_str_t *contact,
			const sipua_str_t *mime_type, const sipua_str_t *body);
} sipua_callback;

int sipua_init(char *user, char *passwd, char *domain, int port, 
		sipua_callback *cbk, int max_calls, int reg, int log_level);

int sipua_call_invite(char *call_url, char *content_type, char *msg_body);

int sipua_message_send(char *msg_to, char *mime_type, char *msg_body);

int sipua_cleanup();

int sipua_thread_register(const char *thread_name);

#endif	/* _SIPUA_H_ */
