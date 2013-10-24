#include "syshdr.h"
#include "uudplsn.h"

int uudplsn(char *path)
{
	int sock;
	struct sockaddr_un addr;

	if (path == NULL)
		return -1;

	sock = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (sock < 0) {
		syslog(LOG_DEBUG, "socket() error:%s.", strerror(errno));
		return -1;
	}

	unlink(path);
	bzero(&addr, sizeof(addr));
	addr.sun_family = AF_LOCAL;
	snprintf(addr.sun_path, sizeof(addr.sun_path), path);

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		syslog(LOG_DEBUG, "bind error.");
		return -1;
	}

	syslog(LOG_DEBUG, "UNIX domain socket: %s", path);
	return sock;
}
