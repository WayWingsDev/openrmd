#include "syshdr.h"
#include "tcplsn.h"

#define BACKLOG		2048	/* 2nd argument to listen() */

int tcplsn(int port)
{
	int sock;
	struct sockaddr_in addr;
	int reuse = 1;
	int ret;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		syslog(LOG_DEBUG, "socket() error:%s.", strerror(errno));
		return -1;
	}
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	/* set socket option */
#ifdef _WIN32_
	ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, 
			(const char *)&reuse, sizeof(int));
#else
	ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
#endif
	if (ret != 0) {
		syslog(LOG_DEBUG, "setsockopt error.");
		return -1;
	}

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		syslog(LOG_DEBUG, "bind error.");
		return -1;
	}

	if (listen(sock, BACKLOG) != 0) {
		syslog(LOG_DEBUG, "listen error.");
		return -1;
	}

	return sock;
}
