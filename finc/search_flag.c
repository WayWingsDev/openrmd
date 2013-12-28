#include <stdio.h>
#include "search_flag.h"

//#define _DEBUG_

int search_flag(const void *buff, const int buff_size, 
		const void *flag, const int flag_size, int *left)
{
#ifdef _DEBUG_
	int k;
	printf("[");
	for (k = 0; k < buff_size; k++)
		printf("0x%02X ", ((char *)buff)[k]);
	printf("]\n");
#endif	/* _DEBUG_ */

	int i, j, buff_pos;
	*left = 0;

	for (i = 0; i < buff_size; i++) {
		for (j = 0; j < flag_size; j++) {
			buff_pos = i + j;
			if (((char *)buff)[buff_pos] != ((char *)flag)[j])
				break;
			if ((j + 1) == flag_size) {	/* found */
				*left = i;
				return 0;
			}
			if ((buff_pos + 1) == buff_size) { /* left some bytes */
				*left = buff_size - buff_pos + 1;
				return -1;
			}
		}
	}

	return -1;
}
