#include "syshdr.h"
#include "basename.h"

char *basename(char *path)
{
	char *p = strrchr(path, FINC_SLASH);
	if (p == NULL)
		return path;

	return p + 1;
}
