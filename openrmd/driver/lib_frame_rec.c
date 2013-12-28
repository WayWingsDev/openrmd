#include "lib_frame_rec.h"
#include "lib_special.h"

/* special implementation, normal in lib_special.c */
extern unsigned long special_geterror();
extern int special_init();
extern int special_login(char *ip, int port, char *user, char *pwd);
extern int special_logout(int login_id);
extern unsigned long special_start_record(start_record_info_t *info);
extern int special_record(unsigned long record_handle, char *buff, int bytes, 
		unsigned int bgn_time, unsigned int end_time);
extern int special_stop_record(unsigned long record_handle);

static get_runtime_t get_runtime;

////////////////////////////////////////////////////////////////////////////
// driver interface
////////////////////////////////////////////////////////////////////////////

int rmd_di_rec_get_info(int *device_type)
{
	if (device_type != NULL)
		*device_type = DEV_TYPE;
	return 0;
}

int rmd_di_rec_init(get_runtime_t get_runtime_func)
{
	get_runtime = get_runtime_func;
	return special_init();
}

unsigned long rmd_di_rec_geterror()
{
	return special_geterror();
}

int rmd_di_rec_login(char *ip, int port, char *user, char *pwd)
{
	return special_login(ip, port, user, pwd);
}

int rmd_di_rec_logout(int login_id)
{
	return special_logout(login_id);
}

unsigned int rmd_di_rec_start_record(start_record_info_t *info)
{
	return special_start_record(info);
}

int rmd_di_rec_record(unsigned long record_handle, char *buff, int bytes, 
		unsigned int bgn_time, unsigned int end_time)
{
	if (record_handle == -1 || record_handle == 0)
		return -1;
	return special_record(record_handle, buff, bytes, bgn_time, end_time);
}

int rmd_di_rec_stop_record(unsigned long record_handle)
{
	if (record_handle == -1 || record_handle == 0)
		return -1;
	return special_stop_record(record_handle);
}

#ifdef NONE_BLOCKING

/*
 * buffer form:
 * --------------------------------------------------------------------------
 * | bytes |  bgn  |  end  | buffer | bytes |  bgn  |  end  | buffer |  ... |
 * --------------------------------------------------------------------------
 * | 4Bytes| 4Bytes| 4Bytes|  ...   | 4Bytes| 4Bytes| 4Bytes|  ...   |  ... |
 */
#define BUFF_SIZE		(1024 * 1024)	/* M bytes */
#define ADDI_SIZE		12
#define BLOCK_TIMEOUT		20		/* seconds */
#define CHECK_EXIT_TIMEOUT	10		/* seconds */

/* none blocking handle type */
typedef struct {
	unsigned long   handle;
	unsigned long   eno;
	pthread_mutex_t mtx;
	pthread_cond_t  cond;
	void            *buff[2];		/* double buffer */
	int             master_buff_bytes;	/* bytes in master buffer */
	int             slave_buff_bytes;	/* bytes in slave buffer */
	void		*master_buff_ptr;	/* point to master buffer */
	void		*slave_buff_ptr;	/* point to slave buffer */
	record_callback_t record_cbk;		/* record callback function */
	stop_record_callback_t stop_record_cbk;	/* stop record callback */
	pthread_t 	tid;
	int             thread_stop;
	sem_t		stop_sem;

	time_t		actual_record_time;
} nb_handle_t;

static void nb_handle_free(nb_handle_t *h)
{
	if (h == NULL)
		return;

	pthread_mutex_destroy(&h->mtx);
	pthread_cond_destroy(&h->cond);
	sem_destroy(&h->stop_sem);
	if (h->buff[0])
		free(h->buff[0]);
	if (h->buff[1])
		free(h->buff[1]);
	free(h);
}

static int record(nb_handle_t *h)
{
	int bytes;
	unsigned int bgn, end;
	int pos;
	char *buff = h->slave_buff_ptr;
	int total_bytes = h->slave_buff_bytes;

	for (pos = 0; (pos + ADDI_SIZE) < total_bytes; 
			pos += (ADDI_SIZE + bytes)) {
		bytes = *(int *)&buff[pos];
		if (bytes > FRAME_SIZE)
			break;
		bgn = *(int *)&buff[pos + 4];
		end = *(int *)&buff[pos + 8];

		if (h->record_cbk(h->handle, &buff[pos + ADDI_SIZE], bytes, 
					bgn, end) == -1)
			return -1;
		h->actual_record_time = get_runtime();
	}
	return 0;
}

static void *nb_record_thread(void *arg)
{
	nb_handle_t *h = (nb_handle_t *)arg;
	struct timespec ts;
	int ret;
	void *tmp_ptr;

	while (h->thread_stop == 0) {
		if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
			syslog(LOG_DEBUG, "clock_gettime() failed:%d", errno);
			h->eno = -1;
			break;
		}
		ts.tv_sec += CHECK_EXIT_TIMEOUT;

		pthread_mutex_lock(&h->mtx);

		ret = pthread_cond_timedwait(&h->cond, &h->mtx, &ts);
		if (ret == ETIMEDOUT) {
			pthread_mutex_unlock(&h->mtx);
			continue;
		}

		/* swap double buffer's pointer */
		tmp_ptr = h->master_buff_ptr;
		h->master_buff_ptr = h->slave_buff_ptr;
		h->slave_buff_ptr = tmp_ptr;
		h->slave_buff_bytes = h->master_buff_bytes;
		h->master_buff_bytes = 0;

		pthread_mutex_unlock(&h->mtx);

		if (record(h) == -1) {
			pthread_mutex_lock(&h->mtx);
			h->eno = -1;
			pthread_mutex_unlock(&h->mtx);
			break;
		}
	}

	while ((ret = sem_wait(&h->stop_sem)) == -1 && errno == EINTR)
		continue;

	return NULL;
}

unsigned long nb_start_record(unsigned long handle, 
		record_callback_t record_cbk,
		stop_record_callback_t stop_record_cbk)
{
	if (handle == -1)
		return -1;

	nb_handle_t *p = NULL;

	p = malloc(sizeof(nb_handle_t));
	if (p == NULL)
		goto err;

	p->handle = handle;
	p->eno = 0;
	pthread_mutex_init(&p->mtx, NULL);
	pthread_cond_init(&p->cond, NULL);
	p->master_buff_ptr = p->buff[0] = malloc(BUFF_SIZE);
	p->slave_buff_ptr = p->buff[1] = malloc(BUFF_SIZE);
	if (p->buff[0] == NULL || p->buff[1] == NULL)
		goto err;
	p->master_buff_bytes = 0;
	p->slave_buff_bytes = 0;
	p->record_cbk = record_cbk;
	p->stop_record_cbk = stop_record_cbk;
	p->thread_stop = 0;
	if (sem_init(&p->stop_sem, 0, 0) != 0)
		goto err;
	p->actual_record_time = get_runtime();

	if (pthread_create(&p->tid, NULL, nb_record_thread, (void *)p) != 0)
		goto err;

	return (unsigned long)p;

err:
	stop_record_cbk(handle);
	nb_handle_free(p);
	return -1;
}

int nb_record(unsigned long record_handle, char *buff, int bytes, 
		unsigned int bgn_time, unsigned int end_time)
{
	nb_handle_t *h = (nb_handle_t *)record_handle;

	pthread_mutex_lock(&h->mtx);
	if (h->eno != 0) {
		pthread_mutex_unlock(&h->mtx);
		return -1;
	}

	if ((get_runtime() - h->actual_record_time) > BLOCK_TIMEOUT) {
		pthread_mutex_unlock(&h->mtx);
		syslog(LOG_DEBUG, "--- record timeout\n");
		return -1;
	}

	if ((h->master_buff_bytes + ADDI_SIZE + bytes) > BUFF_SIZE) {
		pthread_mutex_unlock(&h->mtx);
		pthread_cond_signal(&h->cond);
		return 0;
	}

	memcpy(h->master_buff_ptr + h->master_buff_bytes, &bytes, 4);
	memcpy(h->master_buff_ptr + h->master_buff_bytes + 4, &bgn_time, 4);
	memcpy(h->master_buff_ptr + h->master_buff_bytes + 8, &end_time, 4);
	memcpy(h->master_buff_ptr + h->master_buff_bytes + 12, buff, bytes);
	h->master_buff_bytes += ADDI_SIZE + bytes;

	pthread_mutex_unlock(&h->mtx);
	pthread_cond_signal(&h->cond);
	return 0;
}

int nb_stop_record(unsigned long handle)
{
	nb_handle_t *p = (nb_handle_t *)handle;
	p->thread_stop = 1;
	sem_post(&p->stop_sem);
	pthread_join(p->tid, NULL);

	p->stop_record_cbk(p->handle);
	nb_handle_free(p);
	return 0;
}

#endif	/* NONE_BLOCKING */
