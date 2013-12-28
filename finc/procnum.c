#include <stdio.h>
#include <stdlib.h>
#include "procnum.h"

int procnum(char *proc_name)
{
	char cmd[256], buff[64] = "";
	FILE *fd;

	snprintf(cmd, sizeof(cmd), "ps -eo comm | grep '%s' | wc -l",
			proc_name);

	if ((fd = popen(cmd, "r")) == NULL) {
		pclose(fd);
		return -1;
	}

	if (fgets(buff, sizeof(buff), fd) == NULL) {
		pclose(fd);
		return -1;
	}

	pclose(fd);
	return atoi(buff);
}

//int main()
//{
//	printf("%d\n", procnum("test"));
//	return 0;
//}
