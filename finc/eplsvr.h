#ifndef _EPLSVR_H_
#define _EPLSVR_H_

typedef int (*eplsvr_client_in_callback_t)(int sock, char *ip, void *param);
typedef int (*eplsvr_client_out_callback_t)(int sock, void *param);
typedef int (*eplsvr_data_in_callback_t)(int sock, char *buff, int bytes, 
		void *param);
typedef int (*eplsvr_data_recv_callback_t)(int sock, void *param);

typedef struct {
	eplsvr_client_in_callback_t client_in;
	eplsvr_client_out_callback_t client_out;
	eplsvr_data_in_callback_t data_in;
	eplsvr_data_recv_callback_t data_recv;
} eplsvr_callback_t;

/* remove socket from epoll list only (not close it) */
#define EPLSVR_REMOVE_SOCK_ONLY	1

/* epoll server type */
typedef struct eplsvr_t eplsvr_t;

/* add a tcp listen socket in a new epoll wait queue, return the epoll server
 * node if success or NULL if failed.
 */
#define EPLSVR_NONBLOCK		0x01
#define EPLSVR_RECV_CALLBACK	0x02
eplsvr_t *eplsvr_create(int lsnfd, int options, int buff_size, 
		int max_clients, eplsvr_callback_t *cb, void *param);

/* destory a epoll server. */
int eplsvr_destory(eplsvr_t *eplsvr);

#endif	/* _EPLSVR_H_ */
