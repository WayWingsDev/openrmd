#ifndef _DIFFSEC_H_
#define _DIFFSEC_H_

/* calculte the differenct (seconds) between time2 and time1.
 * e.g., time1 = "2012-07-19 00:00:00", time2 = "2012-07-19 00:00:59", 
 * the differenct time is 59 seconds.
 */
long diffsec(int year1, int mon1, int day1, int hour1, int min1, int sec1,
		int year2, int mon2, int day2, int hour2, int min2, int sec2);

#endif	/* _DIFFSEC_H_ */
