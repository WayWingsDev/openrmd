#include "syshdr.h"
#include "get_absolute_filename.h"
#include "getrpath.h"

int get_absolute_filename(const char *rel_name, char *abs_name, int size)
{
	char path[PATH_MAX];

	/* set config file name */
	if (getrpath(path, sizeof(path)) == -1)
		return -1;
	snprintf(abs_name, size, "%s%c%s", path, FINC_SLASH, rel_name);
	return 0;
}
