#include "getsvrip.h"
#include "syshdr.h"

char *getsvrip(const int client_sock)
{
	char *svrip = NULL;
 	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr_in);

	if (getsockname(client_sock, (struct sockaddr *)&addr, &len) == 0)
		svrip = inet_ntoa(addr.sin_addr);

	return svrip;
}



