#ifndef _DBG_MSG_H_
#define _DBG_MSG_H_

#include <stdarg.h>

void dbg_msg(const char *fmt, ...)
{
#if DBG_MSG
	va_list ap;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
#endif
}

#endif	/* _DBG_MSG_H_ */
