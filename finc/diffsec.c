#include "diffsec.h"
#include <time.h>

long diffsec(int year1, int mon1, int day1, int hour1, int min1, int sec1,
		int year2, int mon2, int day2, int hour2, int min2, int sec2)
{
	struct tm t1 = {0}, t2 = {0};

	t1.tm_year	= year1 - 1900;
	t1.tm_mon	= mon1 - 1;
	t1.tm_mday	= day1;
	t1.tm_hour	= hour1;
	t1.tm_min	= min1;
	t1.tm_sec	= sec1;

	t2.tm_year	= year2 - 1900;
	t2.tm_mon	= mon2 - 1;
	t2.tm_mday	= day2;
	t2.tm_hour	= hour2;
	t2.tm_min	= min2;
	t2.tm_sec	= sec2;

	return (mktime(&t2) - mktime(&t1));
}
