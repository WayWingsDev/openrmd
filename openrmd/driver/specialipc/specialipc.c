#include "specialipc.h"

static void session_free(realplay_handle_t *handle)
{
	if (handle == NULL)
		return;

	pthread_mutex_destroy(&handle->login_id_mtx);
	sem_destroy(&handle->play_sem);
	sem_destroy(&handle->stop_sem);
	free(handle);
}

static void rtp_slice_callback(char *buff, int bytes, void *arg)
{
	realplay_handle_t *handle = (realplay_handle_t *)arg;
	handle->data_cb((unsigned long)handle, buff, bytes, handle->param);
}

static void recv_data(realplay_handle_t *handle)
{
	char buff[FRAME_SIZE];
	int bytes;
	char left_buff[FRAME_SIZE + RTP_MTU + 20];
	int left_bytes = 0;
	uint16_t seq = 0;
	uint32_t ssrc = 10, ts_curr = 0, ts_inc = 1200;

	while (1) {
		bytes = recv(handle->login_id, buff, sizeof(buff), 0);
		if (bytes <= 0)
			return;

		if (handle->pkt_cb) {
			handle->pkt_cb(left_buff, sizeof(left_buff), 
				&left_bytes, buff, bytes, 
				&seq, ssrc, &ts_curr, ts_inc, 
				rtp_slice_callback, handle);
		} else {
			handle->data_cb((unsigned long)handle, buff, bytes, 
					handle->param);
		}
	}
}

static void *realplay_thread(void *arg)
{
	realplay_handle_t *p = (realplay_handle_t *)arg;
	int first = 0;
	struct timespec ts;
	int ret;

	while (1) {
		pthread_mutex_lock(&p->login_id_mtx);
		p->play_ret = p->fp_realplay_start(p);
		pthread_mutex_unlock(&p->login_id_mtx);

		if (first == 0) {
			first = 1;
			sem_post(&p->play_sem);
			if (p->play_ret == -1)
				break;
		}

		if (p->play_ret == -1) {
			clock_gettime(CLOCK_REALTIME, &ts);
			ts.tv_sec += RECONN_DELAY;
			SEM_TIMEDWAIT(&p->stop_sem, &ts, &ret);

			if (p->stop_sess == 1)
				break;
			continue;
		}

		p->state_cb(1, p->param);
		recv_data(p);
		p->state_cb(0, p->param);

		pthread_mutex_lock(&p->login_id_mtx);
		p->fp_realplay_stop(p);
		pthread_mutex_unlock(&p->login_id_mtx);

		if (p->stop_sess == 1)
			break;
	}

	return NULL;
}

/* packetization: 0-not need packetization to rtp packages, 1-need */
unsigned long specialipc_start_realplay(realplay_info_t *info)
{
	realplay_handle_t *p;
	struct timespec ts;
	int ret;

	p = calloc(1, sizeof(realplay_handle_t));
	if (p == NULL)
		goto err;
	memcpy(p, info, sizeof(realplay_handle_t));

	pthread_mutex_init(&p->login_id_mtx, NULL);

	if (sem_init(&p->play_sem, 0, 0) || sem_init(&p->stop_sem, 0, 0))
		goto err;
	p->play_ret = -1;
	p->stop_sess = 0;

	ret = pthread_create(&p->play_tid, NULL, realplay_thread, p);
	if (ret != 0)
		goto err;

	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += 5;
	SEM_TIMEDWAIT(&p->play_sem, &ts, &ret);
	if (p->play_ret == -1) {
		pthread_join(p->play_tid, NULL);
		goto err;
	}

	syslog(LOG_DEBUG, "specialipc play session: %lu", (unsigned long)p);
	return (unsigned long)p;

err:
	session_free(p);
	syslog(LOG_DEBUG, "specialipc play session error");
	return -1;
}

int specialipc_stop_realplay(unsigned long handle)
{
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (handle == -1 || handle == 0)
		return -1;

	p->stop_sess = 1;

	pthread_mutex_lock(&p->login_id_mtx);
	/* let recv() return immediately */
	if (p->login_id != -1)
		shutdown(p->login_id, SHUT_RD);
	pthread_mutex_unlock(&p->login_id_mtx);

	sem_post(&p->stop_sem);

	pthread_join(p->play_tid, NULL);
	session_free(p);

	syslog(LOG_DEBUG, "specialipc stop session: %lu", handle);
	return 0;
}
