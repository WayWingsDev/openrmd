#include "syshdr.h"

#ifdef _LINUX_
#include <stdio_ext.h>
#endif

#include "syslog.h"
#include "getfullname.h"
#include "getrname.h"

static FILE *syslog_fp = NULL;
static char syslog_tag[PATH_MAX] = "";
static int  syslog_pri = LOG_DEBUG;		/* default level */

void openlog(const char *ident, int opt, int fac)
{
	char fname[PATH_MAX];
	char prog[512];
	int  ret;

	if (strlen(syslog_tag) > 0)		/* already open */
		return;

	ret = getrname(prog, sizeof(prog));
	if (fac == LOG_LOCAL0 || ret == -1)
		syslog_fp = stdout;
	else {
#if defined(_LINUX_)
		snprintf(fname, sizeof(fname), "/var/log/%s.log", prog);
#elif defined(_WIN32_)
		getfullname(fname, sizeof(fname));
#endif

		if ((syslog_fp = fopen(fname, "a")) == NULL)
			syslog_fp = stdout;
	}

#if defined(_LINUX_)
	setlinebuf(syslog_fp);	/* set stream to line buffered */
#endif

#define TAG_LEN	 strlen(syslog_tag)
#define TAG_LEFT (PATH_MAX - TAG_LEN)
	if (strlen(prog) > 0)
		snprintf(&syslog_tag[TAG_LEN], TAG_LEFT, "%s", prog);
	if (opt & LOG_PID)
		snprintf(&syslog_tag[TAG_LEN], TAG_LEFT, "[%d]", (int)getpid());
	if (opt & LOG_CONS)
		/* TODO */;
	if (opt & LOG_PERROR)
		/* TODO */;

	snprintf(&syslog_tag[TAG_LEN], TAG_LEFT, ":");
}

void syslog(int pri, const char *fmt, ...)
{
	va_list ap;
	char buf[LOG_MAX_LEN] = "";
	char st[32] = "";
	struct tm tm;
	time_t tt;

	if (pri > syslog_pri)
		return;

	if (syslog_fp == NULL)	/* not open syslog yet */
		openlog(NULL, LOG_CONS | LOG_PID, LOG_LOCAL0);

	tt = time(NULL);
#if defined(_LINUX_)
	if (localtime_r(&tt, &tm) != NULL)
		strftime(st, sizeof(st), "%F %T", &tm);
#elif defined(_WIN32_)
	if (localtime_s(&tm, &tt) == 0)
		strftime(st, sizeof(st), "%Y-%m-%d %H:%M:%S", &tm);
#endif

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	fprintf(syslog_fp, "%s %s %s\n", st, syslog_tag, buf);
}

void closelog()
{
	if (syslog_fp != NULL && syslog_fp != stdout)
		fclose(syslog_fp);
}

int setlogmask(int mask)
{
	int syslog_mask = 0xFF;
	syslog_pri = LOG_DEBUG;

	while (syslog_mask > mask) {
		syslog_mask = (syslog_mask >> 1) - 1;
		syslog_pri--;
	}

    return syslog_pri;
}
