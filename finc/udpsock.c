#include "udpsock.h"
#include "udplsn.h"

int udpsock(char *svr_ip, int svr_port, struct sockaddr_in *svr_addr, 
		int local_port)
{
	int sock;

	if (local_port == -1)
		sock = socket(AF_INET, SOCK_DGRAM, 0);
	else
		sock = udplsn(local_port);
	if (sock < 0) {
		syslog(LOG_DEBUG, "socket() error:%s.", strerror(errno));
		return -1;
	}

	bzero(svr_addr, sizeof(struct sockaddr_in));
	svr_addr->sin_family = AF_INET;
	svr_addr->sin_addr.s_addr = inet_addr(svr_ip);
	svr_addr->sin_port = htons(svr_port);

	return sock;
}
