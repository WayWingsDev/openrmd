#ifndef _STRTIME_H_
#define _STRTIME_H_

#define STRTIME_FMT_YMD		1	/* %Y-%m-%d */
#define STRTIME_FMT_YMD_HMS	2	/* %Y-%m-%d %H:%M:%S */
#define STRTIME_FMT_YMD_HMS_MS	3	/* %Y-%m-%d %H:%M:%S-%ms */

/* NOTE: if now=0, use the current time; if now=-1, buff is NULL. */
int strtime(char *buff, int buff_size, int fmt, unsigned long now);

#endif	/* _STRTIME_H_ */
