#include "syshdr.h"
#include "eplsvr.h"
#include "set_nonblock.h"

#define EPOLL_SIZE	100		/* unuse since Linux 2.6.8 */
#define EVENTS		1024		/* max events on epoll_wait() */

struct eplsvr_t {
	int eplfd;
	int lsnfd;
	int options;
	int buff_size;
	int max_clients;
	int cur_clients;
	unsigned long handle;
	eplsvr_callback_t *cb;
	void *param;
};

static inline void client_in(eplsvr_t *ep)
{
	int sock;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	struct epoll_event ev;

	sock = accept(ep->lsnfd, (struct sockaddr *)&addr, &len);
	if (sock < 0) {
		syslog(LOG_DEBUG, "accept error: %s", strerror(errno));
		return;
	}

	if (ep->cur_clients + 1 > ep->max_clients) {
		syslog(LOG_DEBUG, "clients number overflow");
		goto err;
	}

	/* set client's socket to O_NONBLOCK */
	if (ep->options & EPLSVR_NONBLOCK)
		set_nonblock(sock);
//		fcntl(sock, F_SETFL, O_NONBLOCK | fcntl(sock, F_GETFL));

	ev.events = EPOLLIN;
	ev.data.fd = sock;
	if (epoll_ctl(ep->eplfd, EPOLL_CTL_ADD, sock, &ev) == -1) {
		syslog(LOG_DEBUG, "epoll_ctl() err[%d]", errno);
		goto err;
	}

	if (ep->cb->client_in(sock, inet_ntoa(addr.sin_addr), 
				ep->param) == -1) {
		epoll_ctl(ep->eplfd, EPOLL_CTL_DEL, sock, NULL);
		goto err;
	}

	ep->cur_clients++;
	return;

err:
	close(sock);
}

static inline void client_out(eplsvr_t *ep, int sock)
{
	/* Regardless of whether epoll_ctl() is successful at below, we muse
	 * call the statement. */
	ep->cb->client_out(sock, ep->param);

	if (epoll_ctl(ep->eplfd, EPOLL_CTL_DEL, sock, NULL) != 0) {
		syslog(LOG_ERR, "remove client error: %s[fd=%d]",
				strerror(errno), sock);
	}
	close(sock);
	ep->cur_clients--;
}

static inline void data_in(eplsvr_t *ep, int sock)
{
	if (ep->options & EPLSVR_RECV_CALLBACK) {
		int ret;
		ret = ep->cb->data_recv(sock, ep->param);
		if (ret == -1)
			goto err;
		else if (ret == EPLSVR_REMOVE_SOCK_ONLY) {
			epoll_ctl(ep->eplfd, EPOLL_CTL_DEL, sock, NULL);
			ep->cur_clients--;
		}
	} else {
		char buff[ep->buff_size];
		int bytes;

		bytes = recv(sock, buff, sizeof(buff), 0);
		if (bytes <= 0)
			goto err;

		if (ep->cb->data_in) {
			if (ep->cb->data_in(sock, buff, bytes, ep->param) != 0)
				goto err;
		}
	}

	return;

err:
	client_out(ep, sock);
}

static void *loop_thread(void *arg)
{
	eplsvr_t *ep = (eplsvr_t *)arg;

	int fds, i;
	struct epoll_event evs[EVENTS];

	while (1) {
		fds = epoll_wait(ep->eplfd, evs, EVENTS, -1);
		if (fds == -1 && errno != EINTR) {
			syslog(LOG_ERR, "epoll_wait(): %s", strerror(errno));
			//continue;
			exit(1);
		}

		for (i = 0; i < fds; i++) {
			if (evs[i].data.fd == ep->lsnfd)  /* client comming */
				client_in(ep);
			else if (evs[i].events & EPOLLIN) /* data comming */
				data_in(ep, evs[i].data.fd);
			else	/* error */
				client_out(ep, evs[i].data.fd);
		}
	}

	return NULL;
}

eplsvr_t *eplsvr_create(int lsnfd, int options, int buff_size, 
		int max_clients, eplsvr_callback_t *cb, void *param)
{
	eplsvr_t *ep;
	struct epoll_event ev;

	signal(SIGPIPE, SIG_IGN);

	ep = malloc(sizeof(eplsvr_t));
	if (ep == NULL)
		return NULL;

	ep->eplfd = epoll_create(EPOLL_SIZE);
	if (ep->eplfd == -1) {
		syslog(LOG_DEBUG, "epoll_create() error[%d]", errno);
		goto err;
	}
	ep->lsnfd = lsnfd;
	ep->options = options;
	ep->buff_size = buff_size;
	ep->max_clients = max_clients;
	ep->cur_clients = 0;
	ep->cb = cb;
	ep->param = param;

	ev.events = EPOLLIN;
	ev.data.fd = lsnfd;
	if (epoll_ctl(ep->eplfd, EPOLL_CTL_ADD, lsnfd, &ev) == -1) {
		syslog(LOG_DEBUG, "epoll_ctl() error[%d]", errno);
		goto err;
	}

	if (pthread_create(&ep->handle, NULL, loop_thread, ep) != 0) {
		syslog(LOG_DEBUG, "create loop_thread error[%d]", errno);
		goto err;
	} else
		pthread_detach((pthread_t)ep->handle);

	return ep;

err:
	if (ep) {
		close(ep->eplfd);
		free(ep);
	}
	return NULL;
}

int eplsvr_destory(eplsvr_t *eplsvr)
{
	if (eplsvr == NULL)
		return -1;

	close(eplsvr->eplfd);
	return 0;
}
