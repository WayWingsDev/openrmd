#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include "localip.h"

int localip(const char *interface, char *ip, const int ip_size)
{
	char cmd[256], buff[64] = "";
	FILE *fd;

	snprintf(cmd, sizeof(cmd), "ifconfig %s | grep 'inet addr'"
			"| awk '{print $2}' | awk -F: '{printf $2}'", 
			interface);

	fd = popen(cmd, "r");
	if (fd == NULL) {
		pclose(fd);
		return -1;
	}

	if (fgets(buff, sizeof(buff), fd) == NULL) {
		pclose(fd);
		return -1;
	}

	snprintf(ip, ip_size, buff);
	pclose(fd);
	return 0;
}
