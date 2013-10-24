#include <string.h>
#include "read_flag.h"
#include "search_flag.h"
#include "recvn.h"

int read_flag(int fd, const void *flag, const int flag_size, 
		const int max_bytes)
{
	char buff[flag_size];	/* buff size should equal flag_size */
	int left = 0;
	int bytes;
	int ret;
	int total_bytes = 0;

	while (1) {
		bytes = sizeof(buff) - left;
		if (left > 0)
			memmove(buff, &buff[bytes], left);
		if (recvn(fd, &buff[left], bytes, 0) != bytes) /* read error */
			goto err;

		ret = search_flag(buff, sizeof(buff), flag, flag_size, &left);
		if (ret == 0) 	/* found */
			return 0;

		if (max_bytes == 0)
			continue;

		total_bytes += (bytes - left);
		if (total_bytes >= max_bytes)
			goto err;
	}

err:
	return -1;
}
