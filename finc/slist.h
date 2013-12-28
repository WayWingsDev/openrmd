#ifndef _SLIST_H_
#define _SLIST_H_

/* single list */

#include "ds_comm.h"

/* list type */
typedef struct slist_t slist_t;

/* list node */
typedef struct slist_t slist_node_t;

/* initialize a new list */
slist_t *slist_init();

/* add a new node into list, return 0 if success or -1 if failed */
inline int slist_add(slist_t **list, void *data);
inline int slist_add_by_opt(int opt, slist_t **list, void *data, 
		ds_cmpfunc_t cmp, void *val);

/* delete a node from list */
inline int slist_del(slist_t **list, ds_cmpfunc_t cmp, void *val, 
		ds_callback_t cb, void *param);

/* get a node from list */
inline int slist_entry(slist_t *list, ds_cmpfunc_t cmp, void *val, void **node);

/*  */
inline int slist_modify(slist_t *list, ds_cmpfunc_t cmp, void *old_val, 
		ds_callback_t cb, void *param);

/* return the itmes number in list. */
inline int slist_size(slist_t *list);

/* return 1(TRUE) if list is empty. Otherwise, return 0(FALSE). */
inline int slist_empty(slist_t *list);

/*  */
inline void slist_for_each(slist_t *list, ds_callback_t cb, void *param);

/*  */
void slist_clear(slist_t **list, ds_callback_t cb, void *param);

/*  */
void slist_destory(slist_t **list, ds_callback_t cb, void *param);

#endif	/* _SLIST_H_ */
