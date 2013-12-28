#include "syshdr.h"
#include "tcpconn.h"

int tcpconn(const char *ip, int port, int timeout)
{
	int sock;
	struct sockaddr_in addr;
	struct timeval tmo;

#if defined(_LINUX_)
	int old_flags = 0;
#else
	unsigned long argp = 1;
	fd_set r;
#endif

	if (ip == NULL)
		return -1;

	if (port <= 0)
		return -1;

	/* create a socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		goto err;

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
#if defined(_LINUX_)
	if (inet_pton(AF_INET, ip, &addr.sin_addr) != 1)
#else
	if ((addr.sin_addr.s_addr = inet_addr(ip)) == INADDR_NONE)
#endif
		goto err;

	if (timeout > 0) {
		tmo.tv_sec = timeout;
		tmo.tv_usec = 0;

#if defined(_LINUX_)
		old_flags = fcntl(sock, F_GETFL);
		if (old_flags == -1)
			goto err;
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tmo, sizeof(tmo));
#elif defined(_WIN32_)
		/* set to none-blocking */
		if (ioctlsocket(sock, FIONBIO, &argp) == SOCKET_ERROR) 
			goto err; 
#endif
	}

	/* connect to server */
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
#if defined(_WIN32_)
		if (timeout > 0 && GetLastError() != WSAEWOULDBLOCK)
#endif
			goto err;
	}
	

	if (timeout > 0) {
#if defined(_LINUX_)
		if (fcntl(sock, F_SETFL, old_flags) == -1)
			goto err;
#elif defined(_WIN32_)
		FD_ZERO(&r);     
		FD_SET(sock, &r);         
		if (select(0, 0, &r, 0, &tmo) <= 0)
			goto err;

		/* restore to blocking */
		argp = 0;
		if (ioctlsocket(sock, FIONBIO, &argp) == SOCKET_ERROR)
			goto err;
#endif
	}

	return sock;

err:
	if (sock != -1) {
#if defined(_WIN32_)
		closesocket(sock);
#else
		close(sock);
#endif
	}
	return -1;
}
