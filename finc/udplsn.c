#include "syshdr.h"
#include "udplsn.h"

int udplsn(int port)
{
	int sock;
	struct sockaddr_in addr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		return -1;

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0)
		return -1;

	return sock;
}
