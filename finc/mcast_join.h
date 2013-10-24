#ifndef _MCAST_JOIN_H_
#define _MCAST_JOIN_H_

#include "syshdr.h"

int mcast_join(char *grp_ip, int grp_port, struct sockaddr_in *grp_addr);

#endif	/* _MCAST_JOIN_H_ */
