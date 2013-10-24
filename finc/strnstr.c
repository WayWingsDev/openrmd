#include <string.h>

#include "strnstr.h"

char *strnstr(const char *s1, const char *s2, size_t n)
{
	char tmp[n], *p;

	memcpy(tmp, s1, n);
	tmp[n] = '\0';
	if ((p = strstr(tmp, s2)) == NULL)
		return NULL;

	return (char *)&s1[p - tmp];
}
