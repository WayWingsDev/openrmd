#ifndef _RMD_SIPUAS_H_
#define _RMD_SIPUAS_H_

char rmd_sipuas_server_uri[256];

/* start sip uas */
int rmd_sipuas_start();

/* stop sip uas */
int rmd_sipuas_stop();

/* trigger teardown in server side (add a close invite event into my queue) */
void rmd_sipuas_trigger_hangup(int msg_from_sip_thread, const char *callid);

/* send sip message */
void rmd_sipuas_send_msg(int msg_from_sip_thread, 
		char *dst_uri, char *mime_type, char *msg_body);

#endif	/* _RMD_SIPUAS_H_ */
