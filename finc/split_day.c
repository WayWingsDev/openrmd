#include <stdio.h>
#include <time.h>
#include "split_day.h"

#define DAY_SECONDS	(24 * 60 * 60)

typedef struct {
	time_t t1;
	time_t t2;
} node_t;

static int get_node(void *data, void *param)
{
	node_t *p = (node_t *)data;
	node_t *node = (node_t *)param;

	node->t1 = p->t1;
	node->t2 = p->t2;
	return 0;
}

split_handle_t *split_day_init(split_time_t *bgn, split_time_t *end)
{
	struct tm tm_end = {0}, tm_bgn = {0}, tm_zero = {0};
	time_t tt_end, tt_bgn, tt_zero;
	stk_t *stack;
	node_t *node;
	
	tm_end.tm_year	= end->year - 1900;
	tm_end.tm_mon	= end->mon - 1;
	tm_end.tm_mday	= end->day;
	tm_end.tm_hour	= end->hour;
	tm_end.tm_min	= end->min;
	tm_end.tm_sec	= end->sec;
	tm_bgn.tm_year	= bgn->year - 1900;
	tm_bgn.tm_mon	= bgn->mon - 1;
	tm_bgn.tm_mday	= bgn->day;
	tm_bgn.tm_hour	= bgn->hour;
	tm_bgn.tm_min	= bgn->min;
	tm_bgn.tm_sec	= bgn->sec;
	tm_zero.tm_year	= end->year - 1900;
	tm_zero.tm_mon	= end->mon - 1;
	tm_zero.tm_mday	= end->day;

	tt_end = mktime(&tm_end);
	tt_bgn = mktime(&tm_bgn);
	tt_zero= mktime(&tm_zero);

	if (tt_end < tt_bgn)
		return NULL;

	stack = stack_init();

	int loop = 1;
	while (loop) {
		if (tt_zero <= tt_bgn) {
			tt_zero = tt_bgn;
			loop = 0;
		}

		node = malloc(sizeof(node_t));
		if (node == NULL)
			return NULL;
		node->t1 = tt_zero;
		node->t2 = tt_end;
		if (stack_push(stack, (void *)node) == -1)
			return NULL;

		tt_end = tt_zero - 1;
		tt_zero -= DAY_SECONDS;
	}

	return (split_handle_t *)stack;
}

int split_day_next(split_handle_t *handle, split_time_t *t1, split_time_t *t2)
{
	if (handle == NULL || t1 == NULL || t2 == NULL)
		return -1;

	stk_t *stack = (stk_t *)handle;
	node_t node;
	struct tm tm_t1, tm_t2;

	if (stack_pop(stack, get_node, &node) == -1)
		return -1;

	if (localtime_r(&node.t1, &tm_t1) == NULL ||
			localtime_r(&node.t2, &tm_t2) == NULL)
		return -1;

	t1->year= tm_t1.tm_year + 1900;
	t1->mon = tm_t1.tm_mon + 1;
	t1->day = tm_t1.tm_mday;
	t1->hour= tm_t1.tm_hour;
	t1->min = tm_t1.tm_min;
	t1->sec = tm_t1.tm_sec;
	t2->year= tm_t2.tm_year + 1900;
	t2->mon = tm_t2.tm_mon + 1;
	t2->day = tm_t2.tm_mday;
	t2->hour= tm_t2.tm_hour;
	t2->min = tm_t2.tm_min;
	t2->sec = tm_t2.tm_sec;

	return 0;
}

int split_day_destory(split_handle_t *handle)
{
	stk_t *stack = (stk_t *)handle;
	stack_destory(stack, NULL, NULL);
	return 0;
}
