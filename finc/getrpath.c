#include "syshdr.h"
#include "getrpath.h"

int getrpath(char *buff, int buff_size)
{
	char *p;

	memset(buff, 0, buff_size);

	if (readlink("/proc/self/exe", buff, buff_size) <= 0)
		return -1;

	if ((p = strrchr(buff, FINC_SLASH)) == NULL)
		return -1;

	memset(p, 0, strlen(p));
	return 0;
}
