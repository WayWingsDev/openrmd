#include "syshdr.h"
#include "set_send_timeout.h"

int set_send_timeout(int sock, int seconds)
{
#if defined(_WIN32_)
	int tmo = seconds * 1000;

	return setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&tmo, 
			sizeof(tmo));
#else
	struct timeval tmo;
	tmo.tv_sec = seconds;
	tmo.tv_usec = 0;

	return setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tmo, 
			sizeof(struct timeval));
#endif
}
