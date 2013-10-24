#ifndef _DS_COMM_H_
#define _DS_COMM_H_

#include "syshdr.h"

#ifdef _WIN32_
#pragma warning(push)
#pragma warning(disable: 4311)
#endif

#define SORT_ASC	0x01		/* sort by asc order */
#define SORT_DEC	0x02		/* sort by dec order */
#define NONE_REPEAT	0x04		/* have no repeat node */

/* callback function typedef */
typedef int (*ds_callback_t)(void *data, void *param);
typedef int (*ds_cmpfunc_t)(void *data, void *param);
typedef int (*ds_callback_2mp_t)(void *data, void *param1, void *param2);
typedef int (*ds_callback_mp_t)(void *data, void *param1, void *param2, 
	void *param3);

/* default callback functions */
/* compare by value */
static inline int ds_cmp_val(void *a, void *b)
{
	if ((int)a < (int)b)
		return -1;
	else if ((int)a == (int)b)
		return 0;
	else
		return 1;
}

/* compare by string */
static inline int ds_cmp_str(void *s1, void *s2)
{
	return strcmp((char *)s1, (char *)s2);
}

/* compare nothing, return zero forever */
static inline int ds_cmp_none(void *a, void *b)
{
	return 0;
}

/* free the node's data */
static inline int ds_free_callback(void *data, void *param)
{
	if (data)
		free(data);
	return 0;
}

/* do nothing */
static inline int ds_none_callback(void *data, void *param)
{
	return 0;
}

/* modify the value */
static inline int ds_modify_callback(void *data, void *param)
{
	*(int *)data = (int)param;
	return 0;
}

#ifdef _WIN32_
#pragma warning(pop)
#endif

#endif	/* _DS_COMM_H_ */
