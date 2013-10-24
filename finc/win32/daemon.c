#include "syshdr.h"
#include "daemon.h"

int daemon(int nochdir, int noclose)
{
	FreeConsole();
	return 0;
}
