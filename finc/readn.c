#include "syshdr.h"
#include "readn.h"

inline int readn(int fd, void *buf, int n)
{
	int readed = 0, left = n, bytes;

	while (left > 0) {
		bytes = read(fd, buf + readed, left);
		if (bytes == -1 && errno == EINTR)
			continue;
		if (bytes <= 0)
			return bytes;

		readed += bytes;
		left -= bytes;
	}

	return n;
}
