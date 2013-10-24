#include "rtspsvr.h"
#include "syshdr.h"
#include "eplsvr.h"
#include "tcplsn.h"
#include "freads.h"
#include "recvn.h"
#include "getsvrip.h"
#include "getcliip.h"
#include "set_keepalive.h"
#include "hash.h"

#define SESS_TABLE_SIZE	1000	/* client session hash table size */
#define KEEPALIVE_IDEL	60	/* start keeplives after period(sec) */
#define KEEPALIVE_CNT	6	/* number of keepalives before death */
#define KEEPALIVE_INTV	10	/* interval between keepalives */

/* rtsp message info (from client) */
typedef struct {
	int  client_fd;

	char method[RTSP_METHOD_LEN];
	char url[RTSP_URL_LEN];
	char date[32];
	char fld[sizeof(rtsp_hdr_fld)/RTSP_HDR_LEN][RTSP_HDRCON_LEN];
	char *content;
	int  content_length;

	rtspsvr_callback_t *cb;
} msg_t;

/* rtsp message respone callback typedef */
typedef int (*method_callback_t)(msg_t *, rtspsvr_cbp_t *);

/* rtsp server session info */
typedef struct {
	int client_fd;
	char sid[RTSP_SID_LEN + 1];	/* session id */
} session_t;

static eplsvr_callback_t *eplsvr_cb = NULL;
static hash_table_t *session_table = NULL;
static uint32_t session_id = 1; 	/* 2^32 == 0xFFFFFFFF */
static rtspsvr_callback_t *rtspsvr_cb = NULL;

inline unsigned int hash_func_sess_table(const int table_size, void *data)
{
	session_t *sess = (session_t *)data;
	return (unsigned int)sess->client_fd % table_size;
}

inline int cmp_func_sess(void *data, void *param)
{
	session_t *sess = (session_t *)data;
	return (sess->client_fd == (int)param ? 0 : -1);
}

#define SHOW_MSG 0
static inline void show_msg(char *buff, int bytes)
{
#if SHOW_MSG
	int i;
	printf("........ ");
	for (i = 0; i < bytes; i++)
		printf("%c", buff[i]);
	printf("\n");
#endif
}

static int handle_options(msg_t *msg, rtspsvr_cbp_t *cbp)
{
	char buff[RTSP_CMD_BUFF];

	snprintf(buff, sizeof(buff), 
			"%s 200 OK\r\n"
			"%s: %s\r\n"
			"%s: %s\r\n"
			"%s: %s, %s, %s, %s, %s, %s, %s, %s\r\n\r\n", 
			RTSP_VER, 
			rtsp_hdr_fld[CSEQ], msg->fld[CSEQ], 
			rtsp_hdr_fld[DATE], msg->date, 
			rtsp_hdr_fld[PUBLIC], RTSP_OPTIONS, RTSP_DESCRIBE, 
			RTSP_SETUP, RTSP_PLAY, RTSP_PAUSE, RTSP_TEARDOWN, 
			RTSP_GET_PARAM, RTSP_SET_PARAM);
	if (send(msg->client_fd, buff, strlen(buff), 0) < 0)
		return -1;
	return 0;
}

static int get_url(msg_t *msg, char *url, int url_size)
{
	char *p;

	p = strchr(&msg->url[RTSP_PREFIX_LEN], '/');
	if (p == NULL || strlen(p) <= 1)
		return -1;
	snprintf(url, url_size, p + 1);
	return 0;
}

static int handle_describe(msg_t *msg, rtspsvr_cbp_t *cbp)
{
	char buff[RTSP_CMD_BUFF];

	if (get_url(msg, cbp->url, sizeof(cbp->url)) != 0)
		return -1;

	if (msg->cb->describe(cbp) != 0)
		return -1;

	if (cbp->sdp == NULL)
		return -1;

	snprintf(buff, sizeof(buff), 
			"%s 200 OK\r\n"
			"%s: %s\r\n"
			"%s: %s\r\n"
			"%s: %s/\r\n"
			"%s: application/sdp\r\n"
			"%s: %d\r\n\r\n%s",
			RTSP_VER, 
			rtsp_hdr_fld[CSEQ], msg->fld[CSEQ], 
			rtsp_hdr_fld[DATE], msg->date,
			rtsp_hdr_fld[CONTENT_BASE], msg->url, 
			rtsp_hdr_fld[CONTENT_TYPE], 
			rtsp_hdr_fld[CONTENT_LENGTH], \
			strlen(cbp->sdp), cbp->sdp);
	free(cbp->sdp);
	if (send(msg->client_fd, buff, strlen(buff), 0) < 0)
		return -1;
	return 0;
}

static int get_trans(msg_t *msg, char *trans, char *cast, 
		int *cli_rtp_port, int *cli_rtcp_port)
{
	if (sscanf(msg->fld[TRANSPORT], "%[^;];%[^;];", trans, cast) != 2)
		return -1;
	if (rtsp_isudp(trans)) {
		char *p = strstr(msg->fld[TRANSPORT], "client_port=");
		if (p == NULL)
			return -1;
		if (sscanf(p, "client_port=%d-%d", 
					cli_rtp_port, cli_rtcp_port) != 2)
			return -1;
	}
	return 0;
}

static int add_session(int client_fd, char *sid)
{
	session_t *sess = malloc(sizeof(session_t));
	if (sess == NULL)
		return -1;
	sess->client_fd = client_fd;
	snprintf(sess->sid, sizeof(sess->sid), sid);

	if (hash_add(session_table, (void *)sess) != 0) {
		free(sess);
		return -1;
	}
	return 0;
}

static int handle_setup(msg_t *msg, rtspsvr_cbp_t *cbp)
{
	char buff[RTSP_CMD_BUFF];

	if (cbp->sdp)
		free(cbp->sdp);
	if (get_url(msg, cbp->url, sizeof(cbp->url)) != 0)
		return -1;
	if (get_trans(msg, cbp->trans, cbp->cast, &cbp->cli_rtp_port, 
				&cbp->cli_rtcp_port) != 0)
		return -1;

	snprintf(cbp->sid, sizeof(cbp->sid), "RTSP-%08X", session_id);
	snprintf(msg->fld[SESSION], RTSP_HDRCON_LEN, cbp->sid);
	if (msg->cb->setup(cbp) != 0)
		return -1;
	if (add_session(msg->client_fd, cbp->sid) != 0) {
		msg->cb->teardown(cbp->sid);
		return -1;
	}
	if (++session_id >= (1 << 31))
		session_id = 1;

	snprintf(buff, sizeof(buff),
			"%s 200 OK\r\n"
			"%s: %s\r\n"
			"%s: %s\r\n"
			"%s: RTP/AVP;unicast;destination=%s;"
			"source=%s;client_port=%d-%d;server_port=%d-%d;"
			"ssrc=%s;PLAY\r\n"
			"%s: %s\r\n"
			"\r\n", 
			RTSP_VER, 
			rtsp_hdr_fld[CSEQ], msg->fld[CSEQ], 
			rtsp_hdr_fld[DATE], msg->date, 
			rtsp_hdr_fld[TRANSPORT], cbp->cliip,
			cbp->svrip, cbp->cli_rtp_port, cbp->cli_rtcp_port, \
			cbp->svr_rtp_port, cbp->svr_rtp_port + 1,
			cbp->sid,
			rtsp_hdr_fld[SESSION], cbp->sid);
	if (send(msg->client_fd, buff, strlen(buff), 0) < 0)
		return -1;
	return 0;
}

static int rtspsvr_play_succ_callback(void *param)
{
	msg_t *msg = (msg_t *)param;
	char buff[RTSP_CMD_BUFF];

	snprintf(buff, sizeof(buff),
			"%s 200 OK\r\n"
			"%s: %s\r\n"
			"%s: %s\r\n"
			"%s: %s\r\n"
			"%s: %s\r\n"
			"%s: url=%s;seq=0;rtptime=0\r\n"
			"\r\n",
			RTSP_VER, 
			rtsp_hdr_fld[CSEQ], msg->fld[CSEQ], 
			rtsp_hdr_fld[DATE], msg->date, 
			rtsp_hdr_fld[RANGE], msg->fld[RANGE],
			rtsp_hdr_fld[SESSION], msg->fld[SESSION],
			rtsp_hdr_fld[RTP_INFO], msg->url);
	if (send(msg->client_fd, buff, strlen(buff), 0) < 0)
		return -1;
	return 0;
}

static int handle_play(msg_t *msg, rtspsvr_cbp_t *cbp)
{
	if (cbp->sdp)
		free(cbp->sdp);

	return msg->cb->play(msg->fld[SESSION], 
			rtspsvr_play_succ_callback, (void *)msg);
}

static int handle_pause(msg_t *msg, rtspsvr_cbp_t *cbp)
{
	return 0;
}

static int del_session(int client_fd, char *sid, rtspsvr_callback_t *cb)
{
	cb->teardown(sid);
	return 0;
}

static int handle_teardown(msg_t *msg, rtspsvr_cbp_t *cbp)
{
	char buff[RTSP_CMD_BUFF];

	if (cbp->sdp)
		free(cbp->sdp);

	del_session(msg->client_fd, msg->fld[SESSION], msg->cb);

	snprintf(buff, sizeof(buff), 
			"%s 200 OK\r\n"
			"%s: %s\r\n"
			"%s: %s\r\n\r\n",
			RTSP_VER, 
			rtsp_hdr_fld[CSEQ], msg->fld[CSEQ], 
			rtsp_hdr_fld[DATE], msg->date);
	if (send(msg->client_fd, buff, strlen(buff), 0) < 0)
		return -1;
	return 0;
}

static int handle_default(msg_t *msg, rtspsvr_cbp_t *cbp)
{
	char buff[RTSP_CMD_BUFF];

	snprintf(buff, sizeof(buff),
			"%s 200 OK\r\n"
			"%s: %s\r\n"
			"%s: %s\r\n"
			"\r\n",
			RTSP_VER,
			rtsp_hdr_fld[CSEQ], msg->fld[CSEQ],
			rtsp_hdr_fld[SESSION], msg->fld[SESSION]);
	if (cbp->sdp)
		free(cbp->sdp);
	if (send(msg->client_fd, buff, strlen(buff), 0) < 0)
		return -1;
	return 0;
}

static int handle_get_parameter(msg_t *msg, rtspsvr_cbp_t *cbp)
{
	return handle_default(msg, cbp);
}

static inline method_callback_t verify_method(char *method)
{
	if (strcmp(method, RTSP_OPTIONS) == 0)
		return handle_options;
	else if (strcmp(method, RTSP_DESCRIBE) == 0)
		return handle_describe;
	else if (strcmp(method, RTSP_ANNOUNCE) == 0)
		return handle_default;
	else if (strcmp(method, RTSP_SETUP) == 0)
		return handle_setup;
	else if (strcmp(method, RTSP_PLAY) == 0)
		return handle_play;
	else if (strcmp(method, RTSP_PAUSE) == 0)
		return handle_pause;
	else if (strcmp(method, RTSP_TEARDOWN) == 0)
		return handle_teardown;
	else if (strcmp(method, RTSP_GET_PARAM) == 0)
		return handle_get_parameter;
	else if (strcmp(method, RTSP_SET_PARAM) == 0)
		return handle_default;
	else if (strcmp(method, RTSP_REDIRECT) == 0)
		return handle_default;
	else if (strcmp(method, RTSP_RECORD) == 0)
		return handle_default;
	else
		return NULL;
}

static inline int put_msg(method_callback_t *method_cb, msg_t *msg, 
		char *buff, int bytes)
{
	int i, pos, len;

	show_msg(buff, bytes);

	/* method line */
	pos = bytes - strlen(RTSP_VER);
	if (pos > 0 && strncmp(&buff[pos], RTSP_VER, strlen(RTSP_VER)) == 0) {
		if (sscanf(buff, "%s %[^ ] ", msg->method, msg->url) != 2)
			return -1;

		/* invalid rtsp method */
		*method_cb = verify_method(msg->method);
		if (*method_cb == NULL)
			return -1;

		/* invalid rtsp prefix */
		if (strncmp(msg->url, RTSP_PREFIX, RTSP_PREFIX_LEN) != 0)
			return -1;

		return 0;
	}

	/* header field line */
	for (i = 0; i < RTSP_HDR_FLDS; i++) {
		len = strlen(rtsp_hdr_fld[i]);
		if (strncmp(buff, rtsp_hdr_fld[i], len) != 0)
			continue;

		len += 2;
		if (bytes - len <= 0)
			return -1;

		strncpy(msg->fld[i], &buff[len], bytes - len);
		msg->fld[i][bytes - len] = '\0';
		return 0;
	}
	return -1;
}

static inline void fmt_date(char *buff, size_t len)
{
	time_t now = time(NULL);
	bzero(buff, len);
	strftime(buff, len, "%d %b %Y %H:%M:%S GMT", gmtime(&now));
}

static inline int handle_method(method_callback_t method_cb, msg_t *msg, 
		rtspsvr_cbp_t *cbp)
{
	int ret = method_cb(msg, cbp);
	if (msg->content_length > 0)
		free(msg->content);
	return ret;
}

static int client_in_callback(int sock, char *ip, void *param)
{
	syslog(LOG_DEBUG, "[CLIENT:IN]  %s (%d)", ip, sock);
	set_keepalive(sock, KEEPALIVE_IDEL, KEEPALIVE_CNT, KEEPALIVE_INTV);
	return 0;
}

static int hash_del_callback(void *data, void *param)
{
	if (data == NULL)
		return -1;

	session_t *sess = (session_t *)data;

	del_session(sess->client_fd, sess->sid, (rtspsvr_callback_t *)param);
	free(data);
	return 0;
}

static int client_out_callback(int sock, void *param)
{
	syslog(LOG_DEBUG, "[CLIENT:OUT] %s (%d)", getcliip(sock), sock);

	session_t sess = {sock};
	int ret;

	do {
		ret = hash_del(session_table, &sess, cmp_func_sess, 
				(void *)sock, hash_del_callback, param);
	} while (ret == 0);

	return 0;
}

static int data_recv_callback(int sock, void *param)
{
	char buff[RTSP_HDRCON_LEN], *p;
	int bytes, len, ret;
	method_callback_t method_cb = NULL;
	msg_t msg;
	rtspsvr_cbp_t cbp;

	while (1) {
		/* header field */
		p = freads(sock, buff, sizeof(buff), &bytes);
		if (p == NULL || bytes <= 0)
			return -1;

		/* header finish, receive body */
		if (strncmp(buff, RTSP_CRLF, RTSP_CRLF_LEN) == 0)
			break;

		len = bytes - RTSP_CRLF_LEN + 1;
		ret = put_msg(&method_cb, &msg, p, len);
		if (p != buff)
			free(p);
		if (ret != 0) {
			syslog(LOG_DEBUG, "put_msg() error");
			return -1;
		}
	}

	if (method_cb == NULL)
		return -1;

	len = atoi(msg.fld[CONTENT_LENGTH]);
	if (len > 0) {
		p = malloc(len);
		if (p == NULL)
			return -1;

		if (recvn(sock, p, len, 0) <= 0) {
			free(p);
			return -1;
		}
	}

	msg.client_fd = sock;
	fmt_date(msg.date, sizeof(msg.date));
	msg.content = p;
	msg.content_length = len;
	msg.cb = (rtspsvr_callback_t *)param;

	cbp.client_fd = sock;
	snprintf(cbp.svrip, sizeof(cbp.svrip), getsvrip(sock));
	snprintf(cbp.cliip, sizeof(cbp.cliip), getcliip(sock));
	cbp.sdp = NULL;

	return handle_method(method_cb, &msg, &cbp);
}

int rtspsvr_start(int lsnport, int max_clients, rtspsvr_callback_t *cb)
{
	int lsnfd;
	eplsvr_t *svr;
	
	lsnfd = tcplsn(lsnport);
	if (lsnfd == -1)
		return -1;

	eplsvr_cb = calloc(1, sizeof(eplsvr_callback_t));
	if (eplsvr_cb == NULL) {
		close(lsnfd);
		return -1;
	}
	eplsvr_cb->client_in  = client_in_callback;
	eplsvr_cb->client_out = client_out_callback;
	eplsvr_cb->data_recv  = data_recv_callback;

	session_table = hash_init(SESS_TABLE_SIZE, hash_func_sess_table);
	rtspsvr_cb = cb;

	svr = eplsvr_create(lsnfd, EPLSVR_NONBLOCK | EPLSVR_RECV_CALLBACK,
			RTSP_CMD_BUFF, max_clients, eplsvr_cb, (void *)cb);
	if (svr == NULL) {
		syslog(LOG_DEBUG, "create epoll server error");
		close(lsnfd);
		free(eplsvr_cb);
		eplsvr_cb = NULL;
		hash_destory(session_table);
		return -1;
	}

	syslog(LOG_DEBUG, "rtspsvr listen on: %d", lsnport);
	return 0;
}

int rtspsvr_stop()
{
	return 0;
}
