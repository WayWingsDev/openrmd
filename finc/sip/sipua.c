#include "sipua.h"

static pjsua_acc_id acc_id;

int sipua_init(char *user, char *passwd, char *domain, int port, 
		sipua_callback *cbk, int max_calls, int reg, int log_level)
{
	pjsua_config cfg;
	pjsua_logging_config log_cfg;
	pjsua_transport_config trans_cfg;
	pjsua_acc_config acc_cfg;
	pj_status_t status;
	char acc_cfg_id[256];
	char acc_cfg_uri[256];

	/* create and initialize pjsua */
	status = pjsua_create();
	if (status != PJ_SUCCESS)
		return -1;

	pjsua_config_default(&cfg);

	if (max_calls > 0 && max_calls <= PJSUA_MAX_CALLS)
		cfg.max_calls = max_calls;
	else if (max_calls > PJSUA_MAX_CALLS)
		cfg.max_calls = PJSUA_MAX_CALLS;

	if (cbk->on_reg_state)
		cfg.cb.on_reg_state2 = cbk->on_reg_state;
	if (cbk->on_incoming_call)
		cfg.cb.on_incoming_call = cbk->on_incoming_call;
	if (cbk->on_call_state)
		cfg.cb.on_call_state = cbk->on_call_state;
	if (cbk->on_pager)
		cfg.cb.on_pager = cbk->on_pager;

	pjsua_logging_config_default(&log_cfg);
	log_cfg.console_level = log_level;
	status = pjsua_init(&cfg, &log_cfg, NULL);
	if (status != PJ_SUCCESS)
		return -1;

	/* creating SIP account */
	pjsua_transport_config_default(&trans_cfg);
	trans_cfg.port = port;
	status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &trans_cfg, NULL);
	if (status != PJ_SUCCESS)
		return -1;

	pjsua_acc_config_default(&acc_cfg);
	snprintf(acc_cfg_id, sizeof(acc_cfg_id), "sip:%s@%s", user, domain);
	snprintf(acc_cfg_uri, sizeof(acc_cfg_uri), "sip:%s", domain);
	acc_cfg.id = pj_str(acc_cfg_id);
	if (reg)
		acc_cfg.reg_uri = pj_str(acc_cfg_uri);
	acc_cfg.cred_count = 1;
	acc_cfg.cred_info[0].realm = pj_str(domain);
	acc_cfg.cred_info[0].scheme = pj_str("digest");
	acc_cfg.cred_info[0].username = pj_str(user);
	acc_cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
	acc_cfg.cred_info[0].data = pj_str(passwd);

	status = pjsua_acc_add(&acc_cfg, PJ_TRUE, &acc_id);
	if (status != PJ_SUCCESS)
		return -1;

	/* Initialization is done, now start pjsua */
	status = pjsua_start();
	if (status != PJ_SUCCESS)
		return -1;

	return 0;
}

int sipua_call_invite(char *call_url, char *content_type, char *msg_body)
{
	pj_status_t status;
	pjsua_msg_data msg_data;

	pj_str_t uri = pj_str(call_url);
	pjsua_msg_data_init(&msg_data);
	msg_data.content_type = pj_str(content_type);
	msg_data.msg_body = pj_str(msg_body);

	status = pjsua_call_make_call(acc_id, &uri, NULL, NULL, 
			&msg_data, NULL);
	if (status != PJ_SUCCESS)
		return -1;

	return 0;
}

int sipua_message_send(char *msg_to, char *mime_type, char *msg_body)
{
	pj_str_t to = pj_str(msg_to);
	pj_str_t type = pj_str(mime_type);
	pj_str_t body = pj_str(msg_body);
	
	pjsua_im_send(acc_id, &to, &type, &body, NULL, NULL);
	return 0;
}

int sipua_cleanup()
{
	pjsua_destroy();
	return 0;
}

int sipua_thread_register(const char *thread_name)
{
	sipua_thread_desc desc;
	sipua_thread_t *this_thread;
	sipua_status_t status;

	pj_bzero(desc, sizeof(desc));
	status = pj_thread_register(thread_name, desc, &this_thread);
	if (status != PJ_SUCCESS)
		return -1;
	return 0;
}
