#include "syshdr.h"
#include "getcliip.h"

char *getcliip(const int client_sock)
{
	char *cliip = NULL;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);

	/* Note, getpeername() only can get the name of connected peer 
	 * socket. If that client closed, the function will return ENOTCONN 
	 * error. */
	if (getpeername(client_sock, (struct sockaddr *)&addr, &len) == 0)
		cliip = inet_ntoa(addr.sin_addr);

	return cliip;
}
