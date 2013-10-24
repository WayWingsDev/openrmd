#ifndef _SPLIT_DAY_H_
#define _SPLIT_DAY_H_

#include "stack.h"

typedef struct {
	int year, mon, day, hour, min, sec;
} split_time_t;

typedef stk_t split_handle_t;

split_handle_t *split_day_init(split_time_t *bgn, split_time_t *end);

int split_day_next(split_handle_t *handle, split_time_t *t1, split_time_t *t2);

int split_day_destory(split_handle_t *handle);

#endif	/* _SPLIT_DAY_H_ */
