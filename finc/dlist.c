#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

struct dlist_t {
	dlist_node_t *next;
	dlist_node_t *prev;
	void *data;		/* user's data */
};

dlist_t *dlist_init()
{
	return NULL;
}

inline int dlist_add(dlist_t **list, void *data)
{
	dlist_node_t *node;

	node = malloc(sizeof(dlist_node_t));
	if (node == NULL)
		return -1;

	if (*list) {
		node->prev = (*list)->prev;
		node->next = *list;
		(*list)->prev = node->prev->next = node;
	} else {	/* have no node yet */
		node->next = node->prev = node;
	}
	node->data = data;
	*list = node;

	return 0;
}

inline int dlist_del(dlist_t **list, ds_cmpfunc_t cmp, void *val, 
		ds_callback_t cb, void *param)
{
	dlist_node_t *p;

	if (list == NULL || cmp == NULL || cb == NULL)
		return -1;

	for (p = *list; p; p = (p->next == *list ? NULL : p->next)) {
		if (cmp(p->data, val) == 0) {
			if (p->next == p) {	/* have only one node */
				*list = NULL;
			} else {
				(p->next)->prev = p->prev;
				(p->prev)->next = p->next;

				if (p == *list) /* first node */
					*list = p->next;
			}

			cb(p->data, param);
			free(p);
			return 0;
		}
	}

	return -1;
}

inline int dlist_entry(dlist_t *list, ds_cmpfunc_t cmp, void *val, void **node)
{
	dlist_node_t *p;

	if (list == NULL || cmp == NULL || node == NULL)
		return -1;

	for (p = list; p; p = (p->next == list ? NULL : p->next)) {
		if (cmp(p->data, val) == 0) {
			*node = p->data;
			return 0;
		}
	}
	return -1;
}

inline int dlist_modify(dlist_t *list, ds_cmpfunc_t cmp,
		void *val, ds_callback_t cb, void *param)
{
	void *node;

	if (list == NULL || cmp == NULL || cb == NULL)
		return -1;

	if (dlist_entry(list, cmp, val, &node) == -1)
		return -1;
	if (cb)
		cb(node, param);
	return 0;
}

inline int dlist_size(dlist_t *list)
{
	int n = 0;
	dlist_node_t *p;

	for (p = list; p; p = (p->next == list ? NULL : p->next))
		n++;
	return n;
}

inline int dlist_empty(dlist_t *list)
{
	return (list == NULL ? 1 : 0);
}

inline int dlist_move(dlist_t **list_src, dlist_t **list_dst, 
		ds_cmpfunc_t cmp, void *val)
{
	void *node;
	
	if (list_src == NULL || cmp == NULL)
		return -1;

	if (dlist_entry(*list_src, cmp, val, &node) == -1)
		return -1;

	if (dlist_add(list_dst, node) == -1)
		return -1;

	return dlist_del(list_src, cmp, val, ds_none_callback, NULL);
}

inline void dlist_for_each(dlist_t *list, ds_callback_t cb, void *param)
{
	dlist_node_t *p;

	if (list == NULL || cb == NULL)
		return;

	for (p = list; p; p = (p->next == list ? NULL : p->next))
		cb(p->data, param);
}

inline void dlist_for_each_2mp(dlist_t *list, ds_callback_2mp_t cb, 
		void *param1, void *param2)
{
	dlist_node_t *p;

	if (list == NULL || cb == NULL)
		return;

	for (p = list; p; p = (p->next == list ? NULL : p->next))
		cb(p->data, param1, param2);
}

inline void dlist_for_each_mp(dlist_t *list, ds_callback_mp_t cb, 
		void *param1, void *param2, void *param3)
{
	dlist_node_t *p;

	if (list == NULL || cb == NULL)
		return;

	for (p = list; p; p = (p->next == list ? NULL : p->next))
		cb(p->data, param1, param2, param3);
}

inline void dlist_for_each_del(dlist_t **list, ds_callback_t cb, void *param)
{
	dlist_node_t *p, *tmp;

	if (list == NULL || cb == NULL)
		return;

	for (p = *list; p;) {
		tmp = p;
		(p->next)->prev = p->prev;
		(p->prev)->next = p->next;
		if (p == *list) {	/* first node */
			*list = (p->next == *list ? NULL : p->next);
			p = *list;
		} else
			p = (p->next == *list ? NULL : p->next);

		cb(tmp->data, param);
		free(tmp);
	}
}

inline void dlist_sort(dlist_t **list, int opt)
{
}

void dlist_clear(dlist_t **list, ds_callback_t cb, void *param)
{
	dlist_node_t *p, *tmp;
	ds_callback_t fp = (cb == NULL ? ds_none_callback : cb);

	if (list == NULL)
		return;

	for (p = *list; p;) {
		fp(p->data, param);
		tmp = p;
		p = (p->next == *list ? NULL : p->next);
		free(tmp);
	}
	*list = NULL;
}

void dlist_destory(dlist_t **list, ds_callback_t cb, void *param)
{
	dlist_clear(list, cb, param);
}
