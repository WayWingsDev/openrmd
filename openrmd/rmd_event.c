#include "rmd_event.h"

#ifdef RMD_HAS_RTSPSVR
#include "access/rmd_rtspsvr.h"
#endif

#ifdef RMD_HAS_SIPUAS
#include "access/rmd_sipuas.h"
#endif

#ifdef RMD_HAS_PTZ
#include "rmd_ptz.h"
#endif

#define XML_HDR		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
#define EVENT_TYPE	"<SIP_XML EventType=\"%s\">\r\n"
#define USER_URI	"<User uri=\"%s\"/>\r\n"
#define MEDIA_INFO	"<Media type=\"%d\" id=\"%d-%d\" via=\"%s\" callid=\"%d\"/>\r\n"
#define EVENT_FIN	"</SIP_XML>\r\n"

static int get_xml_val(const char *cnt, const char *key, char *val, 
		const int val_buff_size)
{
	char *p1, *p2;
	memset(val, 0, val_buff_size);

	if ((p1 = strstr(cnt, key)) == NULL || 
			(p2 = strstr(p1 + strlen(key) + 2, "\"")) == NULL)
		return -1;

	int len = p2 - p1 - strlen(key) - 2;
	if (len > val_buff_size)
		len = val_buff_size;
	strncpy(val, p1 + strlen(key) + 2, len);
	return 0;
}

#ifdef RMD_HAS_PTZ
static int get_ptz_info(const char *cnt, ptz_info_t *ptz_info)
{
	char code[64] = "", cmd[32] = "", p1[16] = "", p2[16] = "", 
	     p3[16] = "";
	if (get_xml_val(cnt, "Item Code", code, sizeof(code)) != 0 ||
			get_xml_val(cnt, "Command", cmd, sizeof(cmd)) != 0 ||
			get_xml_val(cnt, "CommandPara1", p1, sizeof(p1)) != 0 ||
			get_xml_val(cnt, "CommandPara2", p2, sizeof(p2)) != 0)
		return -1;

	get_xml_val(cnt, "CommandPara3", p3, sizeof(p3));
	char plat[32];
	if (sscanf(code, "%[^-]-%d-%d-%d", plat, &ptz_info->device_type,
			&ptz_info->device_id, &ptz_info->channel_id) != 4)
		return -1;
	ptz_info->ctl_code = strtoll(cmd, NULL, 0);
	ptz_info->param1 = strtoll(p1, NULL, 0);
	ptz_info->param2 = strtoll(p2, NULL, 0);
	ptz_info->param3 = strtoll(p3, NULL, 0);

	return 0;
}
#endif

/*
 <Item Code="1001-4-101-1" Command="0402" CommandPara1="4" \
 CommandPara2="4" CommandPara3="1">
 */
static void event_ptzcontrol(const char *body)
{
#ifdef RMD_HAS_PTZ
	ptz_info_t info;
<<<<<<< HEAD
	syslog(LOG_DEBUG, "%s", body);
=======
>>>>>>> 64d671fb5303708a1b14f1d09bf9a4c3f9b79e1c

	if (get_ptz_info(body, &info) != 0)
		return;
	if (info.ctl_code >= 0x0101 && info.ctl_code <= 0x0304)
		rmd_ptz_cam(&info);
	else if (info.ctl_code >= 0x0401 && info.ctl_code <= 0x1102)
		rmd_ptz_ptz(&info);
#endif
}

static void event_get_session_list()
{
	printf("TODO: event_get_session_list()\n");
}

static void event_session_stop(int msg_from_sip_thread, const char *body)
{
	char via[16];	/* SIP/RTSP */
	char callid[10];

	if (get_xml_val(body, "via", via, sizeof(via)) != 0 ||
			get_xml_val(body, "callid", callid, 
				sizeof(callid)) != 0)
		return;

	if (strcmp(via, "RTSP") == 0) {
#ifdef RMD_HAS_RTSPSVR
		int sock = atoi(callid);
		rmd_rtspsvr_trigger_hangup(sock);
#endif
	} else if (strcmp(via, "SIP") == 0) {
#ifdef RMD_HAS_SIPUAS
		rmd_sipuas_trigger_hangup(msg_from_sip_thread, callid);
#endif
	}
}

void rmd_event_report_session(char *event, 
		char *user, int device_id, int channel_id,
		int tcp_sock, const char *sid)
{
#ifdef RMD_HAS_SIPUAS
	char buff[512];
	int msg_from_sip_thread;
	char *via;
	int callid;

	if (tcp_sock != -1) {		/* via RTSP */
		msg_from_sip_thread = 0;
		via = "RTSP";
		callid = tcp_sock;
	} else {			/* via SIP */
		msg_from_sip_thread = 1;
		via = "SIP";
		callid = strtol(sid, NULL, 16);
	}

	snprintf(buff, sizeof(buff),
			XML_HDR
			EVENT_TYPE
			USER_URI
			MEDIA_INFO
			EVENT_FIN,
			event,
			user,
			1, device_id, channel_id, via, callid);
	rmd_sipuas_send_msg(msg_from_sip_thread, 
			rmd_sipuas_server_uri, "text/plain", buff);
#endif
}

void rmd_event_trigger_hangup(rmd_session_t *sess)
{
#ifdef RMD_HAS_RTSPSVR
	if (sess->tcp_sock != -1) 	/* via RTSP */
		rmd_rtspsvr_trigger_hangup(sess->tcp_sock);
#endif

#ifdef RMD_HAS_SIPUAS
	if (sess->tcp_sock == -1) 	/* via SIP */
		rmd_sipuas_trigger_hangup(0, sess->sid);
#endif
}

void rmd_event_message_incoming(int msg_from_sip_thread, const char *msg_body)
{
	char e[32];
<<<<<<< HEAD
	syslog(LOG_DEBUG, "%s", msg_body);
=======
>>>>>>> 64d671fb5303708a1b14f1d09bf9a4c3f9b79e1c

	if (get_xml_val(msg_body, "EventType", e, sizeof(e)) != 0)
		return;
	if (strcmp(e, EVENT_PTZCONTROL) == 0)
		event_ptzcontrol(msg_body);
	else if (strcmp(e, EVENT_GET_SESSION_LIST) == 0)
		event_get_session_list();
	else if (strcmp(e, EVENT_SESSION_STOP) == 0)
		event_session_stop(msg_from_sip_thread, msg_body);
}

void rmd_event_reset_sesslst_msgbody(char *buff, int buff_size)
{
	snprintf(buff, buff_size, XML_HDR EVENT_TYPE EVENT_FIN,
			EVENT_RESET_SESSION_LIST);
}
