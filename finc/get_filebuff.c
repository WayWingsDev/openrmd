#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "get_filebuff.h"

char *get_filebuff(char *file_name, int *context_len)
{
	int fd;
	struct stat st;
	char *buff = NULL;
	int buff_size, bytes, pos = 0;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		goto err;

	if (fstat(fd, &st) == -1)
		goto err;

	if (st.st_size == 0)
		goto err;

	buff_size = st.st_size - 1;  /* remove EOF (end of file character) */
	buff = malloc(buff_size);
	if (buff == NULL)
		goto err;

	while ((bytes = read(fd, &buff[pos], buff_size - pos)) > 0) {
		pos += bytes;
	}
	if (bytes < 0)
		goto err;
	close(fd);

	if (context_len)
		*context_len = pos;
	return buff;

err:
	if (fd >= 0)
		close(fd);
	if (buff)
		free(buff);
	if (context_len)
		*context_len = 0;
	return NULL;
}
