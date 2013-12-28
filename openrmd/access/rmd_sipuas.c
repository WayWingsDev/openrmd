#include "rmd_sipuas.h"
#include "rmd.h"
#include "rmd_sessmgr.h"
#include "getcfg.h"
#include "sip/sipua.h"
#include "rmd_event.h"

#ifdef RMD_ELEC_CONVERT
#include "elec_conv.h"
#endif

#include "dlist.h"

#define SIP_CALLID_FMT	"%08X"
#define SID2CALLID(str)	strtol(str, NULL, 16)

static sipua_callback sipua_cbk;
static int sip_inited = 0;

static dlist_t *timeout_callid = NULL;  /* timeout callid list */
static sem_t toc_sem;
static pthread_mutex_t toc_mtx = PTHREAD_MUTEX_INITIALIZER;

static dlist_t *outcoming_msg_lst = NULL;	/* sip message list */
static sem_t outmsg_sem;
static pthread_mutex_t outmsg_mtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	char dst_uri[256];
	char mime_type[32];
	char msg_body[1024];
} outcoming_msg_t;

#ifdef RMD_DUMMY_INVITE
static void dummy_invite_reply(sipua_call_id call_id)
{
	sipua_msg_data msg_data;
	char sdp[256];

	snprintf(sdp, sizeof(sdp), 
			"v=0\r\n"
			"o=- 0 0 IN IP4 0.0.0.0\r\n"
			"s=-\r\n"
			"c=IN IP4 %s\r\n"
			"m=video %d RTP/AVP 110\r\n"
			"a=rtpmap:110 HIK264/90000\r\n"
			"a=fmtp:100 CIF=1\r\n"
			"a=fmtp:100 profile-level-id=420028\r\n"
			"a=sendonly\r\n\r\n",
			local_ip,
			12000);
	sipua_msg_data_init(&msg_data);
	msg_data.content_type = sipua_str("application/sdp");
	msg_data.msg_body = sipua_str(sdp);
	sipua_call_answer(call_id, 200, NULL, &msg_data);
}
#endif

#ifdef RMD_ELEC_CONVERT
static void elec_invite(sipua_call_id call_id, sipua_rx_data *rdata)
{
	sipua_rdata_sdp_info *sdp_info = sipua_rdata_get_sdp_info(rdata);

	if (sdp_info->sdp_err != 0)	/* no valid SDP body */
		return -1;

	char *sdp = sdp_info->body.ptr;
	char *sdp_out = NULL;
	char *line;
	int ret = -1;

	//printf("[%s]\n", sdp);

	/* parse client's ip address */
	line = strstr(sdp, "c=IN IP4 ");
	if (line == NULL)
		goto out;
	if (sscanf(line, "c=IN IP4 %[^\r]", cli_ip) != 1)
		goto out;

	/* parse client's rtp port */
	int cli_rtp_port;
	line = strstr(sdp, "m=video ");
	if (line == NULL)
		goto out;
	if (sscanf(line, "m=video %d", &cli_rtp_port) != 1)
		goto out;

	/* get describe */
	realplay_info_t info;
	rmd_session_t sess;
	driver_t *driver;
	device_t *device;
	channel_t *channel;

	memset(&sess, 0, sizeof(sess));

	const char *code = "110210000103051604";	/* TEST */
	if (code == NULL)
		goto out;
	if (elec_conv_channel(code, &sess) != 0)
		goto out;
	if (rmd_devmgr_lookup_channel(sess.driver_type, sess.device_id, 
				sess.channel_id, &driver, &device, 
				&channel) != 0) {
		syslog(LOG_DEBUG, "channel not exist");
		goto out;
	}

	snprintf(info.ip, sizeof(info.ip), device->ip);
	info.port = device->port;
	info.channel_id = channel->id;

	snprintf(info.plat, sizeof(info.plat), sess.plat);
	info.device_type = sess.device_type;
	if (sess.device_sub_id == 0)
		info.device_id = sess.device_id;
	else
		info.device_id = sess.device_sub_id;

	snprintf(info.local_ip, sizeof(info.local_ip), local_ip);
	if (driver->rmd_di_get_describe(&info, &sdp_out) != 0)
		goto out;

	snprintf(sess.sid, sizeof(sess.sid), callid);
	sess.trans_method = TRANS_VIA_UDP;
	snprintf(sess.stream_opt, sizeof(sess.stream_opt), STREAMOPT_MAIN);
	snprintf(sess.stream_fmt, sizeof(sess.stream_fmt), STREAMFMT_H264);
	ret = rmd_sessmgr_add(&sess, NULL, -1, cli_ip, cli_rtp_port, 
			cli_rtp_port + 1, &info.svr_rtp_port);
	if (ret != 0)
		goto out;

	ret = 0;

out:
	if (ret == 0) {
		sipua_msg_data msg_data;
		sipua_msg_data_init(&msg_data);
		msg_data.content_type = sipua_str("application/sdp");
		msg_data.msg_body = sipua_str(sdp_out);
		sipua_call_answer(call_id, 200, NULL, &msg_data);
	} else
		sipua_call_hangup(call_id, 400, NULL, NULL);
	if (sdp_out)
		free(sdp_out);
}
#endif

#ifdef RMD_DYNAMIC_DEVICES
/*static*/ int parse_sdp_dynamic_test(sipua_call_id call_id, 
		sipua_rx_data *rdata, rmd_session_t *sess, device_t *device, 
		char *cli_ip, int *cli_rtp_port)
{
	sprintf(cli_ip, "192.168.1.7");
	*cli_rtp_port = 9000;
	sess->device_id = 100;
	sess->channel_id = 200;
	device->id = sess->device_id;
	sess->driver_type = 0;
	sprintf(device->ip, "127.0.0.1");
	device->port = 7000;
	sprintf(device->user, "admin");
	sprintf(device->pwd, "12345");

#ifdef RMD_SEND_APPLY_MSG
	const char *user = "sip:Fangxm@192.168.1.7";
	snprintf(sess->user, sizeof(sess->user), user);
#endif

	return 0;
}

int parse_sdp_dynamic(sipua_call_id call_id, sipua_rx_data *rdata, 
		rmd_session_t *sess, device_t *device, char *cli_ip, 
		int *cli_rtp_port)
{
	sipua_rdata_sdp_info *sdp_info = sipua_rdata_get_sdp_info(rdata);

	if (sdp_info->sdp_err != 0)	/* no valid SDP body */
		return -1;

	char *sdp = sdp_info->body.ptr;
	char *line;
	int ret = -1;

	//printf("[%s]\n", sdp);

	/* parse client's ip address */
	line = strstr(sdp, "c=IN IP4 ");
	if (line == NULL)
		goto out;
	if (sscanf(line, "c=IN IP4 %[^\r]", cli_ip) != 1)
		goto out;

	/* parse client's rtp port */
	line = strstr(sdp, "m=video ");
	if (line == NULL)
		goto out;
	if (sscanf(line, "m=video %d", cli_rtp_port) != 1)
		goto out;

	/*
	a=ResID:10001-0016
	a=rtype:14
	a=rip:192.168.1.157
	a=rport:6554
	a=ruser:test
	a=rpwd:test
	*/

	if ((line = strstr(sdp, "a=ResID:")) == NULL)
		goto out;
	if (sscanf(line, "a=ResID:%d-%d", &sess->device_id, 
				&sess->channel_id) != 2)
		goto out;
	device->id = sess->device_id;

	if ((line = strstr(sdp, "a=rtype:")) == NULL)
		goto out;
	if (sscanf(line, "a=rtype:%d", &sess->driver_type) != 1)
		goto out;

	if ((line = strstr(sdp, "a=rip:")) == NULL)
		goto out;
	if (sscanf(line, "a=rip:%s", device->ip) != 1)
		goto out;

	if ((line = strstr(sdp, "a=rport:")) == NULL)
		goto out;
	if (sscanf(line, "a=rport:%d", &device->port) != 1)
		goto out;

	if ((line = strstr(sdp, "a=ruser:")) == NULL)
		goto out;
	if (sscanf(line, "a=ruser:%s", device->user) != 1)
		goto out;

	if ((line = strstr(sdp, "a=rpwd:")) == NULL)
		goto out;
	if (sscanf(line, "a=rpwd:%s", device->pwd) != 1)
		goto out;

#ifdef RMD_SEND_APPLY_MSG
	pjsua_call_info ci;
	char tmp[256];

	pjsua_call_get_info(call_id, &ci);
	sscanf(ci.remote_info.ptr, "%[^<]<%[^>]", tmp, sess->user);
#endif

	ret = 0;

out:
	return ret;
}

static int add_session(rmd_session_t *sess, device_t *device, char *sid, 
		char *cli_ip, int cli_rtp_port, int *svr_rtp_port)
{
	snprintf(sess->sid, sizeof(sess->sid), sid);
	sess->trans_method = TRANS_VIA_UDP;
	snprintf(sess->stream_opt, sizeof(sess->stream_opt), STREAMOPT_MAIN);
	snprintf(sess->stream_fmt, sizeof(sess->stream_fmt), STREAMFMT_H264);
	return rmd_sessmgr_add(sess, device, -1, cli_ip, cli_rtp_port, 
			cli_rtp_port + 1, svr_rtp_port);
}

static char *get_describe(rmd_session_t *sess, device_t *device, 
		int svr_rtp_port)
{
	driver_t *driver;
	char *sdp = NULL;
	realplay_info_t info;

	driver = rmd_devmgr_get_driver(sess->driver_type);
	if (driver == NULL)
		return NULL;

	snprintf(info.ip, sizeof(info.ip), device->ip);
	info.port = device->port;
	snprintf(info.user, sizeof(info.user), device->user);
	snprintf(info.pwd, sizeof(info.pwd), device->pwd);
	info.channel_id = sess->channel_id;
	info.hdr_cb = NULL;
	info.data_cb = NULL;
	info.svr_rtp_port = svr_rtp_port;
	snprintf(info.local_ip, sizeof(info.local_ip), local_ip);
	if (driver->rmd_di_get_describe(&info, &sdp) != 0)
		return NULL;
	return sdp;
}

static void dynamic_invite(sipua_call_id call_id, char *sid,
		sipua_rx_data *rdata)
{
	device_t device;
	rmd_session_t sess;
	int ret = -1;
	char *sdp = NULL;
	char cli_ip[32];
	int cli_rtp_port;
	int svr_rtp_port;

	memset(&sess, 0, sizeof(sess));

	if (parse_sdp_dynamic/*_test*/(call_id, rdata, &sess, &device, cli_ip, 
				&cli_rtp_port) != 0)
		goto out;

	if (add_session(&sess, &device, sid, cli_ip, cli_rtp_port, 
				&svr_rtp_port) != 0)
		goto out;

	sdp = get_describe(&sess, &device, svr_rtp_port);
	if (sdp == NULL) {
		rmd_sessmgr_del(sid);
		goto out;
	}

	ret = 0;

out:
	if (ret == 0) {
		sipua_msg_data msg_data;
		sipua_msg_data_init(&msg_data);
		msg_data.content_type = sipua_str("application/sdp");
		msg_data.msg_body = sipua_str(sdp);
		sipua_call_answer(call_id, 200, NULL, &msg_data);
	} else
		sipua_call_hangup(call_id, 400, NULL, NULL);
	if (sdp)
		free(sdp);
}
#endif

/* notify sip server the media session is NULL */
#ifdef RMD_SEND_APPLY_MSG
static void notify_reset_sesslst()
{
	char buff[256];

	rmd_event_reset_sesslst_msgbody(buff, sizeof(buff));
	rmd_sipuas_send_msg(1, rmd_sipuas_server_uri, "text/plain", buff);
}
#endif

static void on_reg_state(sipua_acc_id acc_id, sipua_reg_info *info)
{
	static int first = 1;
	int code;

	code = info->cbparam->code;
	if (code == PJSIP_SC_OK && first) {
		syslog(LOG_DEBUG, "register success");
#ifdef RMD_SEND_APPLY_MSG
		notify_reset_sesslst();
#endif
	} else if (code != PJSIP_SC_OK && first) {
		syslog(LOG_DEBUG, "register return code: %d\n", code);
	}
	first = 0;
}

static void on_incoming_call(sipua_acc_id acc_id, sipua_call_id call_id,
		sipua_rx_data *rdata)
{
	printf("----> on_incoming_call: %d\n", call_id);
	if (rdata == NULL) {
		sipua_call_hangup(call_id, 400, NULL, NULL);
		return;
	}

	char sid[RMD_SID_LEN + 1];
	snprintf(sid, sizeof(sid), SIP_CALLID_FMT, call_id);

#if defined(RMD_DUMMY_INVITE)
	dummy_invite_reply(call_id);
#elif defined(RMD_ELEC_CONVERT)
	elec_invite(call_id, rdata);
#elif defined(RMD_DYNAMIC_DEVICES)
	dynamic_invite(call_id, sid, rdata);
#endif
}

static void call_ack_received(sipua_call_id call_id, char *sid)
{
	printf("call [%d] ACK received\n", call_id);

#ifdef RMD_DUMMY_INVITE
	return;
#endif

	if (rmd_sessmgr_play(sid, NULL, NULL) != 0) {
		rmd_sessmgr_del(sid);
		sipua_call_hangup(call_id, 400, NULL, NULL);
		return;
	}
}

static void call_terminated(sipua_call_id call_id, char *sid)
{
	printf("call [%d] terminated\n", call_id);
#ifdef RMD_DUMMY_INVITE
	return;
#endif
	rmd_sessmgr_del(sid);
}

static void on_call_state(sipua_call_id call_id, sipua_event *e)
{
	sipua_call_info ci;

	char sid[RMD_SID_LEN + 1];
	snprintf(sid, sizeof(sid), SIP_CALLID_FMT, call_id);

	sipua_call_get_info(call_id, &ci);
	switch (ci.state) {
		case PJSIP_INV_STATE_CONFIRMED:    /* after ACK is received */
			call_ack_received(call_id, sid);
			break;

		case PJSIP_INV_STATE_DISCONNECTED: /* session is terminated */
			call_terminated(call_id, sid);
			break;

		default:
			return;
	}
}

static void on_pager(sipua_call_id call_id, const sipua_str_t *from,
		const sipua_str_t *to, const sipua_str_t *contact,
		const sipua_str_t *mime_type, const sipua_str_t *body)
{
	printf("sip message incoming\n");
	if (body)
		rmd_event_message_incoming(1, body->ptr);
}

static int call_hangup(void *data, void *param)
{
	sipua_call_hangup((int)data, 400, NULL, NULL);
	return 0;
}

static int send_msg(void *data, void *param)
{
	outcoming_msg_t *msg = (outcoming_msg_t *)data;

	sipua_message_send(msg->dst_uri, msg->mime_type, msg->msg_body);
	free(msg);
	return 0;
}

static void *timeout_callid_thread(void *arg)
{
	int ret;

	if (sipua_thread_register("timeout_callid_thread") != 0) {
		syslog(LOG_ERR, "register timeout_callid_thread failed");
		exit(1);
	}

	while (1) {
		SEM_WAIT(&toc_sem, &ret);

		pthread_mutex_lock(&toc_mtx);
		dlist_for_each_del(&timeout_callid, call_hangup, NULL);
		pthread_mutex_unlock(&toc_mtx);
	}

	return NULL;
}

static void *outcoming_msglst_thread(void *arg)
{
	int ret;

	if (sipua_thread_register("outcoming_msglst_thread") != 0) {
		syslog(LOG_ERR, "register outcoming_msglst_thread failed");
		exit(1);
	}

	while (1) {
		SEM_WAIT(&outmsg_sem, &ret);

		pthread_mutex_lock(&outmsg_mtx);
		dlist_for_each_del(&outcoming_msg_lst, send_msg, NULL);
		pthread_mutex_unlock(&outmsg_mtx);
	}

	return NULL;
}

static int create_timeout_callid_thread()
{
	pthread_t tid;

	timeout_callid = dlist_init();
	if (sem_init(&toc_sem, 0, 0) == -1)
		return -1;
	if (pthread_create(&tid, NULL, timeout_callid_thread, NULL) != 0)
		return -1;
	pthread_detach(tid);
	return 0;
}

static int create_outcoming_msglst_thread()
{
	pthread_t tid;

	outcoming_msg_lst = dlist_init();
	if (sem_init(&outmsg_sem, 0, 0) == -1)
		return -1;
	if (pthread_create(&tid, NULL, outcoming_msglst_thread, NULL) != 0)
		return -1;
	pthread_detach(tid);
	return 0;
}

int rmd_sipuas_start()
{
	int ret;
	char user[128];
	char pwd[128];
	char domain[128];
	int port;
	int max_calls;

	if (getcfg(cfg_file, "sip_user", user, GETCFG_STR) != 0 ||
			getcfg(cfg_file, "sip_pwd", pwd, GETCFG_STR) != 0 ||
			getcfg(cfg_file, "sip_server_ip", domain, 
				GETCFG_STR) != 0 ||
			getcfg(cfg_file, "sip_local_port", &port, 
				GETCFG_INT32) != 0) {
		syslog(LOG_ERR, "get sip information error.");
		return -1;
	}

	if (getcfg(cfg_file, "sip_max_calls", &max_calls, GETCFG_INT32) != 0)
		max_calls = 256;

	snprintf(rmd_sipuas_server_uri, sizeof(rmd_sipuas_server_uri), 
			"sip:%s:%d", domain, 5060);

	memset(&sipua_cbk, 0, sizeof(sipua_callback));
	sipua_cbk.on_reg_state = on_reg_state;
	sipua_cbk.on_incoming_call = on_incoming_call;
	sipua_cbk.on_call_state = on_call_state;
	sipua_cbk.on_pager = on_pager;

	ret = sipua_init(user, pwd, domain, port, &sipua_cbk, max_calls, 1, 0);
	if (ret != 0) {
		syslog(LOG_ERR, "sipua_init() failed");
		return -1;
	}

	if (create_timeout_callid_thread() != 0) {
		syslog(LOG_ERR, "create timeout_callid_thread failed");
		return -1;
	}

	if (create_outcoming_msglst_thread() != 0) {
		syslog(LOG_ERR, "create outcoming_msglst_thread failed");
		return -1;
	}

	syslog(LOG_DEBUG, "start sipuas succ");

#ifdef RMD_ELEC_CONVERT
	if (elec_conv_init() != 0)
		return -1;
#endif

	sip_inited = 1;

	return 0;
}

int rmd_sipuas_stop()
{
	if (sip_inited == 1)
		sipua_cleanup();
	return 0;
}

void rmd_sipuas_trigger_hangup(int msg_from_sip_thread, const char *sid)
{
	int call_id;
	int ret;
	
	call_id = SID2CALLID(sid);

	if (msg_from_sip_thread) {
		sipua_call_hangup(call_id, 400, NULL, NULL);
	} else {
		pthread_mutex_lock(&toc_mtx);
		ret = dlist_add(&timeout_callid, (void *)call_id);
		pthread_mutex_unlock(&toc_mtx);
		if (ret == 0)
			sem_post(&toc_sem);
	}
}

void rmd_sipuas_send_msg(int msg_from_sip_thread,
		char *dst_uri, char *mime_type, char *msg_body)
{
	int ret;
	outcoming_msg_t *msg;

	if (msg_from_sip_thread) {
		sipua_message_send(dst_uri, mime_type, msg_body);
	} else {
		/* Via RTSP. I can't send message in this thread (some SIP 
		 * libraries, e.g., PJSIP, not allow call sip functions 
		 * directly). So, put message into my queue first. */
		msg = malloc(sizeof(outcoming_msg_t));
		if (msg == NULL)
			return;

		snprintf(msg->dst_uri, sizeof(msg->dst_uri), dst_uri);
		snprintf(msg->mime_type, sizeof(msg->mime_type), mime_type);
		snprintf(msg->msg_body, sizeof(msg->msg_body), msg_body);

		pthread_mutex_lock(&outmsg_mtx);
		ret = dlist_add(&outcoming_msg_lst, (void *)msg);
		pthread_mutex_unlock(&outmsg_mtx);
		if (ret == 0)
			sem_post(&outmsg_sem);
	}
}
