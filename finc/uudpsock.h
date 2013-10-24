#ifndef _UUDPSOCK_H_
#define _UUDPSOCK_H_

#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>

/* create a UNIX domain client socket(UDP) */
int uudpsock(char *path, struct sockaddr_un *addr);

#endif	/* _UUDPSOCK_H_ */
