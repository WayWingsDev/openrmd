#ifndef _ROLLING_SIGN_H_
#define _ROLLING_SIGN_H_

#include <stdio.h>

/* 
 * NOTE: You maybe to call
 * "setvbuf(stdout, (char *)NULL, _IONBF, 0);" first.
 */
static inline void rolling_sign()
{
	static char sign[] = "|/-\\";
	static int n = 0;
	printf("%c\r", sign[n]);
	fflush(stdout);
	if (++n == sizeof(sign) - 1)
		n = 0;
}

#endif	/* _ROLLING_SIGN_H_ */
