#include "rtspcli.h"
#include "syshdr.h"
#include "tcpconn.h"
#include "set_recv_timeout.h"
#include "freads.h"
#include "recvn.h"
#include "readbuf.h"
#include "base64_decode.h"
#include "udplsn.h"
#include "udpsock.h"
#include "rtp.h"
#include "rtcp.h"

#define CLIENT_NAME		"rtsp_client"
#define TCP_RECV_TIMEOUT	20
#define RTP_RECV_TIMEOUT 	20

/* rtsp message info (from server) */
typedef struct {
	char fld[sizeof(rtsp_hdr_fld)/RTSP_HDR_LEN][RTSP_HDRCON_LEN];
	char *content;
	int  content_length;
} msg_t;

/* rtsp client session info */
typedef struct {
	char url[RTSP_URL_LEN];
	char svr_ip[32];
	int svr_port;
	int cseq;
	char trans[16];
	int pure_tcp_data;
	char sid[RTSP_SID_LEN + 1];
	int svr_rtcp_port;
	uint32_t ssrc;

	int svr_sock;
	int cli_rtp_sock;
	int cli_rtcp_sock;
	struct sockaddr_in rtcp_addr;

	rtspcli_sdp_callback_t sdp_cbk;
	void *sdp_param;
	rtspcli_data_callback_t data_cbk;
	void *data_param;
	rtspcli_get_runtime_t get_runtime;

	sem_t play_sem;
	sem_t stop_sem;
	int play_ret;
	int stop_sess;
	pthread_t play_tid;
	pthread_t rtp_tid;
	pthread_t rtcp_tid;
} session_t;

static time_t normal_get_runtime()
{
	return time(NULL);
}

static int get_svr_info(const char *url, char *ip, int *port)
{
	char ip_port[40];

	if (sscanf(url, "rtsp://%[^/]/", ip_port) != 1)
		return -1;
	if (sscanf(ip_port, "%[^:]:%d", ip, port) != 2)
		*port = RTSP_PORT;
	return 0;
}

static inline int put_fieldline(char *buff, int bytes, 
		char fld[][RTSP_HDRCON_LEN])
{
	int i, len;

	for (i = 0; i < RTSP_HDR_FLDS; i++) {
		len = strlen(rtsp_hdr_fld[i]);
		if (strncmp(buff, rtsp_hdr_fld[i], len) != 0)
			continue;

		len += 2;
		if (bytes - len <= 0)
			return -1;

		strncpy(fld[i], &buff[len], bytes - len);
		return 0;
	}
	return -1;
}

static int recv_response(session_t *sess, msg_t *msg)
{
	char buff[RTSP_HDRCON_LEN], *p;
	int bytes, len, ret;
	char rtsp_ver[8], code_str[8];
	int code;

	bzero(msg, sizeof(msg_t));

	/* read status line */
	p = freads(sess->svr_sock, buff, sizeof(buff), &bytes);
	if (p == NULL || bytes <= 0)
		return -1;

	if (sscanf(p, "%s %d %s", rtsp_ver, &code, code_str) != 3) {
		if (p != buff)
			free(p);
		return -1;
	}
	if (code != 200) {
		if (p != buff)
			free(p);
		return -1;
	}

	while (1) {
		/* header field */
		p = freads(sess->svr_sock, buff, sizeof(buff), &bytes);
		if (p == NULL || bytes <= 0)
			return -1;

		/* header finish, receive body */
		if (strncmp(buff, RTSP_CRLF, RTSP_CRLF_LEN) == 0)
			break;

		bytes = bytes - RTSP_CRLF_LEN + 1;
		ret = put_fieldline(p, bytes, msg->fld);
		if (p != buff)
			free(p);
		if (ret != 0)
			return -1;
	}

	len = atoi(msg->fld[CONTENT_LENGTH]);
	if (len > 0) {
		p = malloc(len);
		if (p == NULL)
			return -1;

		if (recvn(sess->svr_sock, p, len, 0) <= 0) {
			free(p);
			return -1;
		}
	}

	msg->content = p;	/* donn't forget to release it */
	msg->content_length = len;
	return 0;
}

static int send_options(session_t *sess)
{
	char buff[RTSP_CMD_BUFF];
	msg_t msg;

	snprintf(buff, sizeof(buff),
			"%s %s %s\r\n"
			"%s: %d\r\n"
			"%s: %s (%s)\r\n"
			"\r\n",
			RTSP_OPTIONS, sess->url, RTSP_VER,
			rtsp_hdr_fld[CSEQ], sess->cseq++,
			rtsp_hdr_fld[USER_AGENT], CLIENT_NAME, RTSP_AGENT);
	if (send(sess->svr_sock, buff, strlen(buff), 0) < 0)
		return -1;

	if (recv_response(sess, &msg) != 0)
		return -1;

	if (msg.content_length > 0)
		free(msg.content);

	return 0;
}

static int parse_sps(session_t *sess, msg_t *msg)
{
	char *p1, *p2;
	char buff[RTSP_SPS_MAX] = "", *str, sps[RTSP_SPS_MAX + 2];
	int pos = 0;
	buf_t *pb;

	p1 = strstr(msg->content, RTSP_SPS_FIX);
	if (p1 == NULL)
		goto out;

	p1 += strlen(RTSP_SPS_FIX);
	p2 = strstr(p1, "\r\n");
	if (p2 == NULL || p2 - p1 < 0 || p2 - p1 > RTSP_SPS_MAX)
		goto out;
	if (p2 - p1 == 0)
		goto out;

	memset(sps, 0, sizeof(sps));
	strncpy(sps, p1, p2 - p1);
	sps[strlen(sps)] = ',';

	pb = openbuf(sps, strlen(sps));
	if (pb == NULL)
		goto out;

	while ((str = readbuf(pb, ",")) != NULL) {
		pos += base64_decode((uint8_t *)&buff[pos], 
				sizeof(buff) - pos, str);
	}
	closebuf(pb);

	if (pos > RTSP_SPS_MAX) {
		pos = 0;
		return -1;
	}

out:
	sess->sdp_cbk((unsigned long)sess, 
			msg->content, msg->content_length, 
			sps, strlen(sps) - 1,
			buff, pos, 
			sess->sdp_param);
	return 0;
}

static int send_describe(session_t *sess)
{
	char buff[RTSP_CMD_BUFF];
	msg_t msg;
	int ret = 0;

	snprintf(buff, sizeof(buff), 
			"%s %s %s\r\n"
			"%s: %d\r\n"
			"%s: %s (%s)\r\n"
			"%s: application/sdp\r\n"
			"\r\n",
			RTSP_DESCRIBE, sess->url, RTSP_VER,
			rtsp_hdr_fld[CSEQ], sess->cseq++,
			rtsp_hdr_fld[USER_AGENT], CLIENT_NAME, RTSP_AGENT,
			rtsp_hdr_fld[ACCEPT]);
	if (send(sess->svr_sock, buff, strlen(buff), 0) < 0)
		return -1;

	if (recv_response(sess, &msg) != 0)
		return -1;

	if (sess->sdp_cbk)
		ret = parse_sps(sess, &msg);

	if (msg.content_length > 0)
		free(msg.content);

	return ret;
}

static int dispatch_port(session_t *sess)
{
	int port;
	int sock[2];
	static int i = 0;

	while (1) {
		port = RTSP_RTPPORT_MIN + 2 * i++;
		sock[1] = udplsn(port);
		sock[2] = udplsn(port + 1);
		if (sock[1] == -1)
			close(sock[1]);
		if (sock[2] == -1)
			close(sock[2]);

		if (port >= RTSP_RTPPORT_MAX)
			i = 0;

		if (sock[1] != -1 && sock[2] != -1)
			break;
	}
	sess->cli_rtp_sock = sock[1];
	sess->cli_rtcp_sock = sock[2];

	set_recv_timeout(sess->cli_rtp_sock, RTP_RECV_TIMEOUT);
	set_recv_timeout(sess->cli_rtcp_sock, RTCP_RECV_TIMEOUT);
	return port;
}

static int parse_setup(session_t *sess, msg_t *msg)
{
	char *sid = msg->fld[SESSION];
	if (strlen(sid) == 0)
		return -1;
	snprintf(sess->sid, sizeof(sess->sid), sid);

	if (rtsp_isudp(sess->trans)) {
		char *p = strstr(msg->fld[TRANSPORT], "server_port=");
		if (p == NULL)
			return -1;
		int svr_rtp_port;
		if (sscanf(p, "server_port=%d-%d", &svr_rtp_port, 
					&sess->svr_rtcp_port) != 2)
			return -1;

		struct sockaddr_in addr;

		bzero(&addr, sizeof(struct sockaddr_in));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(sess->svr_ip);
		addr.sin_port = htons(sess->svr_rtcp_port);
		sess->rtcp_addr = addr;

		p = strstr(msg->fld[TRANSPORT], "ssrc=");
		if (p == NULL) {
			sess->ssrc = 0;
			return 0;
		}
		char ssrc[17] = "";
		if (sscanf(p, "ssrc=%[^;]", ssrc) != 1)
			return -1;
		sess->ssrc = strtoll(ssrc, NULL, 16);
	}
	return 0;
}

static int send_setup(session_t *sess)
{
	char buff[RTSP_CMD_BUFF];
	msg_t msg;
	int cli_rtp_port = 0;

	if (rtsp_isudp(sess->trans)) {
		cli_rtp_port = dispatch_port(sess);
		if (cli_rtp_port == -1)
			return -1;
	}

	snprintf(buff, sizeof(buff), 
			"%s %s %s\r\n"
			"%s: %d\r\n"
			"%s: %s (%s)\r\n"
			"%s: %s;%s;client_port=%d-%d\r\n\r\n",
			RTSP_SETUP, sess->url, RTSP_VER,
			rtsp_hdr_fld[CSEQ], sess->cseq++,
			rtsp_hdr_fld[USER_AGENT], CLIENT_NAME, RTSP_AGENT,
			rtsp_hdr_fld[TRANSPORT], sess->trans, RTSP_CAST_UNI, 
			cli_rtp_port, cli_rtp_port + 1);
	if (send(sess->svr_sock, buff, strlen(buff), 0) < 0)
		return -1;

	if (recv_response(sess, &msg) != 0)
		return -1;

	if (msg.content_length > 0)
		free(msg.content);

	if (parse_setup(sess, &msg) != 0)
		return -1;

	return 0;
}

static int send_play(session_t *sess)
{
	char buff[RTSP_CMD_BUFF];
	msg_t msg;

	snprintf(buff, sizeof(buff), 
			"%s %s %s\r\n"
			"%s: %d\r\n"
			"%s: %s (%s)\r\n"
			"%s: %s\r\n"
			"%s: npt=%s\r\n"
			"\r\n",
			RTSP_PLAY, sess->url, RTSP_VER,
			rtsp_hdr_fld[CSEQ], sess->cseq++,
			rtsp_hdr_fld[USER_AGENT], CLIENT_NAME, RTSP_AGENT,
			rtsp_hdr_fld[SESSION], sess->sid,
			rtsp_hdr_fld[RANGE], "0.000-");
	if (send(sess->svr_sock, buff, strlen(buff), 0) < 0)
		return -1;

	if (recv_response(sess, &msg) != 0)
		return -1;

	if (msg.content_length > 0)
		free(msg.content);

	return 0;
}

static int send_teardown(session_t *sess)
{
	char buff[RTSP_CMD_BUFF];

	snprintf(buff, sizeof(buff), 
			"%s %s %s\r\n"
			"%s: %d\r\n"
			"%s: %s\r\n"
			"\r\n",
			RTSP_TEARDOWN, sess->url, RTSP_VER,
			rtsp_hdr_fld[CSEQ], sess->cseq++,
			rtsp_hdr_fld[SESSION], sess->sid);
	if (send(sess->svr_sock, buff, strlen(buff), 0) < 0)
		return -1;

	return 0;
}

static int send_set_parameter(session_t *sess, char *content, 
		int content_length)
{
	char buff[RTSP_CMD_BUFF];
	msg_t msg;

	snprintf(buff, sizeof(buff), 
			"%s %s %s\r\n"
			"%s: %d\r\n"
			"%s: %s (%s)\r\n"
			"%s: %s\r\n"
			"%s: %d\r\n"
			"%s: %s\r\n"
			"\r\n"
			"%s",
			RTSP_SET_PARAM, sess->url, RTSP_VER,
			rtsp_hdr_fld[CSEQ], sess->cseq++,
			rtsp_hdr_fld[USER_AGENT], CLIENT_NAME, RTSP_AGENT,
			rtsp_hdr_fld[SESSION], sess->sid,
			rtsp_hdr_fld[CONTENT_LENGTH], content_length,
			rtsp_hdr_fld[CONTENT_TYPE], "text/parameters",
			content);
	if (send(sess->svr_sock, buff, strlen(buff), 0) < 0)
		return -1;

	if (recv_response(sess, &msg) != 0)
		return -1;

	if (msg.content_length > 0)
		free(msg.content);

	return 0;
}

static void *rtp_data_thread(void *arg)
{
	session_t *sess = (session_t *)arg;
	char buff[RTP_SLICE_SIZE];
	int bytes;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	while (1) {
		bytes = recvfrom(sess->cli_rtp_sock, buff, sizeof(buff), 0,
				(struct sockaddr *)&addr, &addrlen);
		if (bytes <= 0 || sess->stop_sess == 1)
			break;
		if (bytes <= RTP_HDR_FIX_SIZE)
			continue;

		//rtp_print_hdr(buff);
		sess->data_cbk((unsigned long)sess, buff, bytes, 
				sess->data_param);
	}

	syslog(LOG_DEBUG, "rtp_data_thread() exit()");
	shutdown(sess->cli_rtcp_sock, SHUT_RD);
	sem_post(&sess->stop_sem);
	return NULL;
}

static void *pure_tcp_data_thread(void *arg)
{
	session_t *sess = (session_t *)arg;
	char buff[1024 * 200];
	int bytes;

	while (1) {
		bytes = recv(sess->svr_sock, buff, sizeof(buff), 0);
		if (bytes <= 0)
			break;
		sess->data_cbk((unsigned long)sess, buff, bytes, 
				sess->data_param);
	}

	syslog(LOG_DEBUG, "pure_tcp_data_thread() exit()");
	sem_post(&sess->stop_sem);
	return NULL;
}

static void *rtp_over_tcp_data_thread(void *arg)
{
	session_t *sess = (session_t *)arg;
	char buff[RTP_SLICE_SIZE];
	const int offset = 4;
	int len, bytes;

	while (1) {
		/* recv length */
		bytes = recvn(sess->svr_sock, buff, offset, 0);
		if (bytes != offset)	/* error */
			break;
		len = ntohs(*(uint16_t *)&buff[2]);
		if (len > sizeof(buff)) {	/* dirty data */
			bytes = recv(sess->svr_sock, buff, sizeof(buff), 0);
			continue;
		}

		/* recv data */
		bytes = recvn(sess->svr_sock, buff, len, 0);
		if (bytes != len)	/* error */
			break;
		if (bytes <= RTP_HDR_FIX_SIZE)
			continue;

		//rtp_print_hdr(buff);
		sess->data_cbk((unsigned long)sess, buff, bytes, 
				sess->data_param);
	}

	syslog(LOG_DEBUG, "pure_tcp_data_thread() exit()");
	sem_post(&sess->stop_sem);
	return NULL;
}

static void *rtcp_thread(void *arg)
{
	session_t *sess = (session_t *)arg;
	char buff[512];
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	rtcp_t *rtcp = NULL;
	int bytes;
	time_t last_send_time = sess->get_runtime();
	time_t last_recv_time = sess->get_runtime();	

	rtcp = rtcp_open(sess->cli_rtcp_sock, sess->rtcp_addr, 
			RTCP_RECEIVER_REPORT);
	if (rtcp == NULL)
		goto out;

	/////////////////////////////////////////////
	char data[RTP_SLICE_SIZE];
	rtp_hdr_t *rtp_hdr = (rtp_hdr_t *)&data[0];
	uint32_t ts_curr = 0, ts_inc = 1200;

	rtp_hdr->ver = RTP_VER;
	rtp_hdr->pad = 0;
	rtp_hdr->ext = 0;
	rtp_hdr->pt = RTP_PT_H264;
	rtp_hdr->ssrc = htonl(sess->ssrc);
//	rtp_hdr->ssrc = htonl(strtoll(sess->sid, NULL, 16));
	rtp_hdr->cc = 0; /* TODO */
	/////////////////////////////////////////////

	while (1) {
		bytes = recvfrom(sess->cli_rtcp_sock, buff, sizeof(buff), 0,
				(struct sockaddr *)&addr, &addrlen);
		if (bytes == 0 || sess->stop_sess == 1)
			break;
		if ((sess->get_runtime() - last_recv_time) >= 60)
			break;
		if (bytes > 12) {
			last_recv_time = sess->get_runtime();	
			if (sess->ssrc == 0) {
				sess->ssrc = ntohl(*(uint32_t *)&buff[4]);
				rtp_hdr->ssrc = htonl(sess->ssrc);
			}
		}

		if ((sess->get_runtime() - last_send_time) > RTCP_SEND_SLOT) {
			rtp_hdr->ts = htonl(ts_curr);
			rtcp_send(rtcp, data, sizeof(data));
			ts_curr += ts_inc;
			last_send_time = sess->get_runtime();
		}
	}

out:
	if (rtcp != NULL)
		rtcp_close(rtcp);

	syslog(LOG_DEBUG, "rtcp_thread() exit()");
	shutdown(sess->cli_rtp_sock, SHUT_RD);
	return NULL;
}

static int session_stop(session_t *sess)
{
	if (sess == NULL)
		return -1;

	if (sess->svr_sock != -1) {
		send_teardown(sess);
		shutdown(sess->svr_sock, SHUT_RD);
		close(sess->svr_sock);
	}
	if (sess->cli_rtp_sock != -1) {
		shutdown(sess->cli_rtp_sock, SHUT_RD);
		close(sess->cli_rtp_sock);
	}
	if (sess->cli_rtcp_sock != -1) {
		shutdown(sess->cli_rtcp_sock, SHUT_RD);
		close(sess->cli_rtcp_sock);
	}

	if (sess->rtp_tid != 0)
		pthread_join(sess->rtp_tid, NULL);
	if (sess->rtcp_tid != 0)
		pthread_join(sess->rtcp_tid, NULL);

	return 0;
}

static void session_free(session_t *sess)
{
	sem_destroy(&sess->play_sem);
	sem_destroy(&sess->stop_sem);
	free(sess);
}

static int session_play(session_t *sess)
{
	int ret;

	sess->cseq = 1;
	sess->ssrc = 0;
	sess->svr_sock = -1;
	sess->cli_rtp_sock = -1;
	sess->cli_rtcp_sock = -1;
	sess->rtp_tid = 0;
	sess->rtcp_tid = 0;

	sess->svr_sock = tcpconn(sess->svr_ip, sess->svr_port, 5);
	if (sess->svr_sock == -1) {
		syslog(LOG_DEBUG, "connect RTSP server error");
		goto err;
	}
	set_recv_timeout(sess->svr_sock, TCP_RECV_TIMEOUT);

	ret = send_options(sess);
	if (ret != 0) {
		syslog(LOG_DEBUG, "send_options() error");
		goto err;
	}

	ret = send_describe(sess);
	if (ret != 0) {
		syslog(LOG_DEBUG, "send_describe() error");
		goto err;
	}

	if (sess->data_cbk == NULL)	/* get sps only */
		return 0;

	ret = send_setup(sess);
	if (ret != 0) {
		syslog(LOG_DEBUG, "send_setup() error");
		goto err;
	}

	ret = send_play(sess);
	if (ret != 0) {
		syslog(LOG_DEBUG, "send_play() error");
		goto err;
	}

	if (rtsp_isudp(sess->trans)) {		/* standard RTP and RTCP */
		ret = pthread_create(&sess->rtp_tid, NULL, 
				rtp_data_thread, sess);
		if (ret != 0)
			goto err;

		ret = pthread_create(&sess->rtcp_tid, NULL, rtcp_thread, sess);
	} else if (sess->pure_tcp_data) {	/* pure tcp data over RTSP */
		ret = pthread_create(&sess->rtp_tid, NULL, 
				pure_tcp_data_thread, sess);
	} else {				/* RTP over TCP */
		ret = pthread_create(&sess->rtp_tid, NULL, 
				rtp_over_tcp_data_thread, sess);
	}

	if (ret != 0)
		goto err;

	return 0;

err:
	session_stop(sess);
	return -1;
}

static void *play_thread(void *arg)
{
	session_t *p = (session_t *)arg;
	int first = 0;
	struct timespec ts;
	int ret;

	while (1) {
		p->play_ret = session_play(p);
		if (first == 0) {
			first = 1;
			sem_post(&p->play_sem);
			if (p->play_ret == -1)
				break;
		}

		if (p->play_ret == -1) {
			clock_gettime(CLOCK_REALTIME, &ts);
			ts.tv_sec += 5;
			SEM_TIMEDWAIT(&p->stop_sem, &ts, &ret);
		} else {
			SEM_WAIT(&p->stop_sem, &ret);
			session_stop(p);
		}

		if (p->stop_sess == 1)
			break;
	}

	return NULL;
}

unsigned long rtspcli_play(char *url, char *trans, 
		rtspcli_sdp_callback_t sdp_cbk, void *sdp_param,
		rtspcli_data_callback_t data_cbk, void *data_param, 
		int pure_tcp_data, rtspcli_get_runtime_t get_runtime_func)
{
	session_t *p;
	struct timespec ts;
	int ret;

	if (!rtsp_isudp(trans) && !rtsp_istcp(trans))
		return -1;

	p = calloc(1, sizeof(session_t));
	if (p == NULL)
		goto err;

	if (sem_init(&p->play_sem, 0, 0) || sem_init(&p->stop_sem, 0, 0))
		goto err;
	p->play_ret = -1;
	p->stop_sess = 0;

	snprintf(p->url, sizeof(p->url), url);
	if (get_svr_info(url, p->svr_ip, &p->svr_port) != 0)
		goto err;

	snprintf(p->trans, sizeof(p->trans), trans);
	p->pure_tcp_data = pure_tcp_data;
	p->sdp_cbk = sdp_cbk;
	p->sdp_param = sdp_param;
	p->data_cbk = data_cbk;
	p->data_param = data_param;
	if (get_runtime_func)
		p->get_runtime = get_runtime_func;
	else
		p->get_runtime = normal_get_runtime;

	ret = pthread_create(&p->play_tid, NULL, play_thread, p);
	if (ret != 0)
		goto err;

	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += 5;
	SEM_TIMEDWAIT(&p->play_sem, &ts, &ret);
	if (p->play_ret == -1) {
		pthread_join(p->play_tid, NULL);
		goto err;
	}

	syslog(LOG_DEBUG, "rtspcli play session: %lu", (unsigned long)p);
	return (unsigned long)p;

err:
	if (p)
		session_free(p);
	syslog(LOG_DEBUG, "rtspcli play session error");
	return -1;
}

int rtspcli_stop(unsigned long sess)
{
	session_t *p = (session_t *)sess;
	if (sess == -1 || sess == 0)
		return -1;

	/* FIXME: If openrmd run under tty, and when you switch tty, the
	 * program will hang-up (rtp_data_thread() can't exit). */
	printf("------------- rtspcli_stop() begin\n");
	p->stop_sess = 1;
	sem_post(&p->stop_sem);
	pthread_join(p->play_tid, NULL);
	session_free(p);
	printf("+++++++++++++ rtspcli_stop() finish\n");

	syslog(LOG_DEBUG, "rtspcli stop session: %lu", sess);
	return 0;
}

int rtspcli_set_parameter(unsigned long sess, char *content, 
		int content_length)
{
	session_t *p = (session_t *)sess;
	if (sess == -1 || sess == 0)
		return -1;

	return send_set_parameter(p, content, content_length);
}
