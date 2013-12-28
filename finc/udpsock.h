#ifndef _UDPSOCK_H
#define _UDPSOCK_H

#include "syshdr.h"

int udpsock(char *svr_ip, int svr_port, struct sockaddr_in *svr_addr, 
		int local_port);

#endif	/* _UDPSOCK_H */
