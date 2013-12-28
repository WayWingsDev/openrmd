#include "syshdr.h"
#include "mkdir_r.h"

int mkdir_r(char *path, unsigned int mode)
{
	char buff[1024];

#ifdef _LINUX_
	snprintf(buff, sizeof(buff), "install -d %s", path);
	return system(buff) == 0 ? 0 : -1;
#else
	int ret;
	snprintf(buff, sizeof(buff), "mkdir %s", path);
	ret = system(buff);

	if (ret == 0 || (ret == 1 && (errno == 0 || errno == 13)))
		return 0;
	return -1;
#endif
}
