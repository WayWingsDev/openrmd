#include "mcast_join.h"
#include "udpsock.h"

int mcast_join(char *grp_ip, int grp_port, struct sockaddr_in *grp_addr)
{
	int sock;
	struct ip_mreq mreq;
	int len = sizeof(struct in_addr);
	unsigned char loop = 0; /* multicast loopback (0: disable 1: enable) */

	sock = udpsock(grp_ip, grp_port, grp_addr, grp_port);
	if (sock == -1)
		goto err;

	memcpy(&mreq.imr_multiaddr, &grp_addr->sin_addr, len);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, 
				sizeof(mreq)) < 0)
		goto err;

	setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));

	return sock;

err:
	syslog(LOG_DEBUG, "%s", strerror(errno));
	if (sock != -1)
		close(sock);
	return -1;
}
