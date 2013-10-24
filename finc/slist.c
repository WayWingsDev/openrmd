#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

struct slist_t {
	slist_node_t *next;
	void *data;		/* user's data */
};

slist_t *slist_init()
{
	return NULL;
}

inline int slist_add(slist_t **list, void *data)
{
	slist_node_t *node;
	
	node = malloc(sizeof(slist_node_t));
	if (node == NULL)
		return -1;
	node->data = data;
	node->next = NULL;

	if (*list == NULL) {
		*list = node;
	} else {
		slist_node_t *p = *list;
		while (p->next != NULL)
			p = p->next;
		p->next = node;
	}

	return 0;
}

inline int slist_add_by_opt(int opt, slist_t **list, void *data, 
		ds_cmpfunc_t cmp, void *val)
{
	slist_node_t *node, *p, *prev = NULL;
	int ret;

	for (p = *list; p; p = p->next) {
		ret = cmp(p->data, val);
		if (ret == 0 && (opt & NONE_REPEAT))
			return 0;
		else if ((ret < 0 && (opt & SORT_ASC)) ||
				(ret > 0 &&(opt & SORT_DEC))) {
			prev = p;
			continue;
		}
		break;
	}

	node = malloc(sizeof(slist_node_t));
	if (node == NULL)
		return -1;

	if (*list == NULL) {		/* have no node yet */
		node->next = NULL;
		*list = node;
	} else if (prev == NULL) {	/* add to begin */
		node->next = *list;
		*list = node;
	} else {
		node->next = p;
		prev->next = node;
	}
	node->data = data;
	return 0;
}

inline int slist_del(slist_t **list, ds_cmpfunc_t cmp, void *val, 
		ds_callback_t cb, void *param)
{
	slist_node_t *p, *prev = NULL;

	if (list == NULL || cmp == NULL || cb == NULL)
		return -1;

	for (p = *list; p; p = p->next) {
		if (cmp(p->data, val) == 0) {
			if (prev == NULL)
				*list = p->next;
			else
				prev->next = p->next;

			cb(p->data, param);
			free(p);
			return 0;
		}
		prev = p;
	}

	return -1;
}

inline int slist_entry(slist_t *list, ds_cmpfunc_t cmp, void *val, void **node)
{
	slist_node_t *p;

	if (list == NULL || cmp == NULL || node == NULL)
		return -1;

	for (p = list; p; p = p->next) {
		if (cmp(p->data, val) == 0) {
			*node = p->data;
			return 0;
		}
	}
	return -1;
}

inline int slist_modify(slist_t *list, ds_cmpfunc_t cmp, void *old_val, 
		ds_callback_t cb, void *param)
{
	void *node;

	if (list == NULL || cmp == NULL || cb == NULL)
		return -1;

	if (slist_entry(list, cmp, old_val, &node) == -1)
		return -1;
	cb(node, param);
	return 0;
}

inline int slist_size(slist_t *list)
{
	int n = 0;
	slist_node_t *p;

	for (p = list; p; p = p->next)
		n++;
	return n;
}

inline int slist_empty(slist_t *list)
{
	return (list == NULL ? 1 : 0);
}

inline void slist_for_each(slist_t *list, ds_callback_t cb, void *param)
{
	slist_node_t *p;

	if (list == NULL || cb == NULL)
		return;

	for (p = list; p; p = p->next)
		cb(p->data, param);
}

void slist_clear(slist_t **list, ds_callback_t cb, void *param)
{
	slist_node_t *p, *tmp;
	ds_callback_t fp = (cb == NULL ? ds_none_callback : cb);

	if (list == NULL)
		return;
	for (p = *list; p;) {
		fp(p->data, param);
		tmp = p;
		p = p->next;
		free(tmp);
	}
	*list = NULL;
}

void slist_destory(slist_t **list, ds_callback_t cb, void *param)
{
	slist_clear(list, cb, param);
}
