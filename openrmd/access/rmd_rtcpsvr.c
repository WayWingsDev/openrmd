#include "rmd.h"
#include "rmd_rtcpsvr.h"
#include "rtcp.h"
#include "rtp.h"
#include "set_recv_timeout.h"
#include "rmd_event.h"

/* rtcp session handle */
typedef struct {
	rtcp_t *rtcp;
	rmd_session_t *sess;
	pthread_t tid;
} rtcp_handle_t;

static void *rtcp_thread(void *arg)
{
	rtcp_handle_t *p = (rtcp_handle_t *)arg;
	char buff[512];
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	int bytes;
	time_t last_send_time = get_runtime();
	time_t last_recv_time = get_runtime();	

	/////////////////////////////////////////////
	char data[RTP_SLICE_SIZE];
	rtp_hdr_t *rtp_hdr = (rtp_hdr_t *)&data[0];
	uint32_t ts_curr = 0;
	uint32_t ts_inc = 1200;

	rtp_hdr->ver = RTP_VER;
	rtp_hdr->pad = 0;
	rtp_hdr->ext = 0;
	rtp_hdr->pt = RTP_PT_H264;
	rtp_hdr->ssrc = htonl(strtoll(p->sess->sid, NULL, 16));
	rtp_hdr->cc = 0; /* TODO */
	/////////////////////////////////////////////

	set_recv_timeout(p->rtcp->sock, RTCP_RECV_TIMEOUT);

	while (1) {
		bytes = recvfrom(p->rtcp->sock, buff, sizeof(buff), 0,
				(struct sockaddr *)&addr, &addrlen);
		if (bytes == 0)
			break;
		if ((get_runtime() - last_recv_time) >= 60) {
			rmd_event_trigger_hangup(p->sess);
			break;
		}
		if (bytes > 12)
			last_recv_time = get_runtime();

		if ((get_runtime() - last_send_time) > RTCP_SEND_SLOT) {
			rtp_hdr->ts = htonl(ts_curr);
			rtcp_send(p->rtcp, data, sizeof(data));
			ts_curr += ts_inc;
			last_send_time = get_runtime();
		}
	}

	return NULL;
}

unsigned long rmd_rtcp_start_session(rmd_session_t *sess)
{
	rtcp_handle_t *p;

	if (sess == NULL)
		return -1;

	p = calloc(1, sizeof(rtcp_handle_t));
	if (p == NULL)
		return -1;

	p->rtcp = rtcp_open(sess->cli_rtp_sock->rtcp_sock, 
			sess->cli_rtp_sock->rtcp_addr, RTCP_SENDER_REPORT);
	if (p->rtcp == NULL)
		goto err;

	p->sess = sess;
	if (pthread_create(&p->tid, NULL, rtcp_thread, p) != 0)
		goto err;

	return (unsigned long)p;

err:
	rmd_rtcp_stop_session((unsigned long)p);
	return -1;
}

int rmd_rtcp_stop_session(unsigned long handle)
{
	rtcp_handle_t *p = (rtcp_handle_t *)handle;
	if (handle == -1 || p == NULL)
		return -1;

	if (p->rtcp->sock != -1)
		shutdown(p->rtcp->sock, SHUT_RD);

	if (p->tid != 0)
		pthread_join(p->tid, NULL);

	rtcp_close(p->rtcp);
	free(p);

	return 0;
}
