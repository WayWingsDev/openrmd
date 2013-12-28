#include "syshdr.h"
#include "strtime.h"

#ifdef _LINUX_
int strtime(char *buff, int buff_size, int fmt, unsigned long now)
{
	struct timeval tv;
	struct tm tm;
	char tmp[32];

	if (buff == NULL)
		return -1;

	buff[0] = '\0';

	if (now == -1)
		return 0;

	if (now == 0) {
		gettimeofday(&tv, NULL);
		if (localtime_r(&tv.tv_sec, &tm) == NULL)
			return -1;
	} else {
		if (localtime_r((time_t *)&now, &tm) == NULL);
	}

	if (fmt == STRTIME_FMT_YMD)
		strftime(buff, buff_size, "%F", &tm);
	else if (fmt == STRTIME_FMT_YMD_HMS)
		strftime(buff, buff_size, "%F %T", &tm);
	else if (fmt == STRTIME_FMT_YMD_HMS_MS) {
		strftime(tmp, sizeof(tmp), "%F %T", &tm);
		snprintf(buff, buff_size, "%s-%03ld", tmp, 
				now == 0 ? tv.tv_usec / 1000 : 0);
	}
	else
		return -1;
	return 0;
}
#endif

#ifdef _WIN32_
int strtime(char *buff, int buff_size, int fmt, unsigned long now)
{
	time_t tt;
	struct tm tm;
	errno_t eno;
	SYSTEMTIME st;

	if (buff == NULL)
		return -1;

	buff[0] = '\0';

	if (now == -1)
		return 0;

	if (fmt == STRTIME_FMT_YMD_HMS_MS && now == 0) {
		GetLocalTime(&st);
		snprintf(buff, buff_size, "%04d-%02d-%02d %02d:%02d:%02d-%03d", 
			st.wYear, st.wMonth, st.wDay, 
			st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		return 0;
	}

	if (now == 0)
		time(&tt);
	else
		tt = now;

	eno = localtime_s(&tm, &tt);
	if (eno != 0)
		return -1;

	if (fmt == STRTIME_FMT_YMD)
		strftime(buff, buff_size, "%Y-%m-%d", &tm);
	else if (fmt == STRTIME_FMT_YMD_HMS)
		strftime(buff, buff_size, "%Y-%m-%d %H:%M:%S", &tm);
	else if (fmt == STRTIME_FMT_YMD_HMS_MS)
		strftime(buff, buff_size, "%Y-%m-%d %H:%M:%S-000", &tm);
	else
		return -1;
	return 0;
}
#endif
