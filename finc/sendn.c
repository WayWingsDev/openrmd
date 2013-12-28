#include <sys/types.h>
#include <sys/socket.h>

#include "sendn.h"

int sendn(int sockfd, void *buf, int n, int flag)
{
	int sended = 0, left = n, bytes;

	while (sended < left) {
		if ((bytes = send(sockfd, buf + sended, left, flag)) <= 0)
			return bytes;

		sended += bytes;
		left -= bytes;
	}

	return n;
}
