#include "rmd_data_callback.h"
#include "rmd.h"
#include "rmd_devmgr.h"
#include "rmd_sessmgr.h"
#include "rolling_sign.h"

#ifdef RMD_HAS_REC
#include "rmd_rec.h"
#endif

#ifdef RMD_HAS_RTSPSVR
#include "access/rmd_rtspsvr.h"
static int tcp_send(void *tcp_sock, void *buff, void *bytes, void *param)
{
	int sock = (int)tcp_sock;
	
	if (send(sock, buff, (int)bytes, 0) < 0 && errno != EAGAIN)
		rmd_rtspsvr_trigger_hangup(sock);
	return 0;
}
#endif

static int rtp_send(void *rtp_sock, void *buff, void *bytes, void *param)
{
	cli_rtp_sock_t *s = (cli_rtp_sock_t *)rtp_sock;

	sendto(s->rtp_sock, buff, (int)bytes, 0, 
			(const struct sockaddr *)&s->rtp_addr,
			(socklen_t)sizeof(struct sockaddr_in));
	return 0;
}

void rmd_data_callback_hdr(char *buff, int bytes, void *param)
{
	channel_t *channel = (channel_t *)param;
	memcpy(channel->hdr_buff, buff, bytes);
	channel->hdr_length = bytes;
}

void rmd_data_callback_real(unsigned long handle, char *buff, 
		int bytes, void *param)
{
	channel_t *channel = (channel_t *)param;

#ifdef RMD_HAS_REC
	if (channel->rec) {
		((rec_driver_t *)channel->rec_driver)->record_callback(buff, 
			bytes, param);
	}
#endif

	pthread_mutex_lock(&channel->mtx);
#ifdef RMD_HAS_RTSPSVR
	dlist_for_each_mp(channel->tcp_clients, tcp_send, (void *)buff, 
			(void *)bytes, param);
#endif
	dlist_for_each_mp(channel->rtp_clients, rtp_send, (void *)buff, 
			(void *)bytes, param);
	pthread_mutex_unlock(&channel->mtx);
}

void realplay_state_callback(int state, void *param)
{
	channel_t *channel = (channel_t *)param;
	channel->camera_state = state;
}
