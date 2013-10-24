#include "syshdr.h"
#include "getfullname.h"

int getfullname(char *buff, int buff_size)
{
	if (readlink("/proc/self/exe", buff, buff_size) <= 0)
		return -1;
	return 0;
}
