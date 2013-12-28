#include <stdio.h>
#include "procnum.h"

int main(int argc, char **argv)
{
	printf("Content type: text/html\n\n");
	if (procnum("openrmd") > 0)
		printf("RUNNING");
	else
		printf("STOP");
	return 0;
}
