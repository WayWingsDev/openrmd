#ifndef _WSA_STARTUP_H_
#define _WSA_STARTUP_H_

static int wsa_startup()
{
	WSADATA wsa;
	static int done = 0;

	if (done == 1)	/* already initialized */
		return 0;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != NO_ERROR)
		return -1;
	done = 1;
	return 0;
}

#endif	/* _WSA_STARTUP_H_ */
