/* get device info from database and write to file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "getcfg.h"
#include "device_cfg.h"

static char device_cfg_file[128] = "";

int add_line(char **buff, int *pos, char *line)
{
	//printf("%s", line);

	int add = strlen(line);
	*buff = (char *)realloc(*buff, *pos + add);
	if (*buff == NULL)
		return -1;
	memcpy(*buff + *pos, line, add);
	*pos += add;
	return 0;
}

int write_file(char *file, char *buff, int length)
{
	int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		printf("create file error\n");
		return -1;
	}

	if (write(fd, buff, length) != length) {
		printf("write error\n");
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s <config file>\n", argv[0]);
		return -1;
	}
	snprintf(cfg_file, sizeof(cfg_file), "%s", argv[1]);

	if (getcfg(cfg_file, "device_cfg_file", device_cfg_file, 
				GETCFG_STR) != 0) {
		printf("get device_cfg_file error\n");
		return -1;
	}
	
	int version;
	if (getcfg(device_cfg_file, "version", &version, GETCFG_INT32) != 0) {
		printf("set version to zero\n");
		version = 0;
	}

	if (device_cfg_init() != 0)
		return -1;

	char *buff = NULL;
	int length = 0;
	int ret = device_cfg_get(version, &buff, &length);

	device_cfg_cleanup();

	if (ret != 0)	/* error */
		return -1;

	if (buff == NULL)	/* not need update */
		return 0;

	ret = write_file(device_cfg_file, buff, length);
	if (buff)
		free(buff);
	return ret;
}
