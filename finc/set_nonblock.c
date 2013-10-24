#include "syshdr.h"
#include "set_nonblock.h"

int set_nonblock(int sock)
{
	return fcntl(sock, F_SETFL, O_NONBLOCK | fcntl(sock, F_GETFL));
}
