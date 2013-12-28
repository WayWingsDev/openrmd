#include <stdio.h>

#include "evenbits_compl.h"

int evenbits_compl(char *buff, int buff_size)
{
	if (buff == NULL || buff_size <= 0)
		return -1;

	int i;
	unsigned char c1, c2;

	for (i = 0; i < buff_size; i++) {
		/* (1). bitwise complement */
		c1 = ~buff[i];

		/* (2). set odd bit to zero on (1)'s result */
		c1 &= 0x2A;

		/* (3). set even bit to zero from original character */
		c2 = buff[i] & 0x55;

		/* (4). get the result by: (2) | (3) */
		buff[i] = c1 | c2;
	}

	return 0;
}
