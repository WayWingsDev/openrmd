#include "syshdr.h"
#include "uudpsock.h"

int uudpsock(char *path, struct sockaddr_un *addr)
{
	if (path == NULL || addr == NULL)
		return -1;

	int sock;

	sock = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (sock < 0) {
		syslog(LOG_DEBUG, "socket() error:%s.", strerror(errno));
		return -1;
	}

	bzero(addr, sizeof(struct sockaddr_un));
	addr->sun_family = AF_LOCAL;
	snprintf(addr->sun_path, sizeof(addr->sun_path), path);

	return sock;
}
