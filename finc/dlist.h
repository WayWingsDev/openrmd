#ifndef _DLIST_H_
#define _DLIST_H_

/* double-loop list */

#include "ds_comm.h"

/* list type */
typedef struct dlist_t dlist_t;

/* list node */
typedef struct dlist_t dlist_node_t;

/* initialize a new list */
dlist_t *dlist_init();

/* add a new node into list, return 0 if success or -1 if failed */
inline int dlist_add(dlist_t **list, void *data);

/* delete a node from list */
inline int dlist_del(dlist_t **list, ds_cmpfunc_t cmp, void *val, 
		ds_callback_t cb, void *param);

/* get a node from list, return 0 if success or -1 if failed */
inline int dlist_entry(dlist_t *list, ds_cmpfunc_t cmp, void *val, void **node);

/*  */
inline int dlist_modify(dlist_t *list, ds_cmpfunc_t cmp,
		void *old_val, ds_callback_t cb, void *param);

/* return the itmes number in list. */
inline int dlist_size(dlist_t *list);

/* return 1(TRUE) if list is empty. Otherwise, return 0(FALSE). */
inline int dlist_empty(dlist_t *list);

/* move a node from list_src to list_dst. return 0 if success, or -1 if 
 * failed. */
inline int dlist_move(dlist_t **list_src, dlist_t **list_dst, 
		ds_cmpfunc_t cmp, void *val);

/*  */
inline void dlist_for_each(dlist_t *list, ds_callback_t cb, void *param);
inline void dlist_for_each_2mp(dlist_t *list, ds_callback_2mp_t cb, 
		void *param1, void *param2);
inline void dlist_for_each_mp(dlist_t *list, ds_callback_mp_t cb, 
		void *param1, void *param2, void *param3);

inline void dlist_for_each_del(dlist_t **list, ds_callback_t cb, void *param);

/*  */
inline void dlist_sort(dlist_t **list, int opt);

/*  */
void dlist_clear(dlist_t **list, ds_callback_t cb, void *param);

/*  */
void dlist_destory(dlist_t **list, ds_callback_t cb, void *param);

#endif	/* _DLIST_H_ */
