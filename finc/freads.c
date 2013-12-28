#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "freads.h"

#define LINE_FLAG	'\n'	/* line end flag */

char *freads(int fd, char *buff, int size, int *bytes)
{
	int index;
	int ret;
	int length = size;
	char *new_buff;

	for (index = 0; index < size; index++) {
		if ((ret = read(fd, &buff[index], 1)) < 0)
			return NULL;
		if (ret == 0 || buff[index] == LINE_FLAG) {
			*bytes = index;
			return buff;
		}
	}

	if ((new_buff = (char*)calloc(length <<= 1, 1)) == NULL)
		return NULL;

	memcpy(new_buff, buff, size);

	while ((ret = read(fd, &new_buff[index], 1)) == 1 && 
			new_buff[index] != LINE_FLAG) {
		index++;
		if (index == length) {
			new_buff = (char*)realloc(new_buff, length <<= 1);
			if (new_buff == NULL) {
				free(new_buff);
				return NULL;
			}
		}
	}
	if (ret < 0) {
		free(new_buff);
		return NULL;
	}

	*bytes = index;
	return new_buff;
}
