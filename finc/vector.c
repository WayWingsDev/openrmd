#include "vector.h"

/* vector item with user's data */
typedef struct vec_item {
	struct vec_item *next;
	struct vec_item *prev;
	void *data;
} vec_item_t;

struct vec_t {
	struct vec_item *head;
	struct vec_item *tail;
	int size;
};

vec_t *vec_init()
{
	vec_t *vec;
	
	vec = malloc(sizeof(vec_t));
	if (vec == NULL)
		return NULL;

	vec->head = vec->tail = NULL;
	vec->size = 0;
	return vec;
}

int vec_push(vec_t *vec, void *data)
{
	vec_item_t *item;

	item = malloc(sizeof(vec_item_t));
	if (item == NULL)
		return -1;

	item->prev = vec->tail;
	item->next = NULL;
	item->data = data;
	if (vec->tail)
		vec->tail->next = item;

	vec->tail = item;
	if (vec->head == NULL)	/* not have any item yet */
		vec->head = item;
	vec->size++;

	return 0;
}

int vec_pop(vec_t *vec, ds_callback_t cb, void *param)
{
	vec_item_t *item;

	if (vec->tail == NULL)
		return -1;
	
	item = vec->tail;
	vec->tail = item->prev;
	vec->size--;

	if (cb)
		cb(item->data, param);

	free(item);
	return 0;
}

int vec_size(vec_t *vec)
{
	return vec->size;
}

int vec_empty(vec_t *vec)
{
	return (vec->size == 0 ? 1 : 0);
}

int vec_entry(vec_t *vec, int index, void **item)
{
	vec_item_t *p = NULL;
	int i;

	if (vec == NULL || vec->size == 0 
			|| index >= vec->size 
			|| item == NULL)
		return -1;

	if (index < vec->size / 2) {
		p = vec->head;
		for (i = 0; i < index; i++)
			p = p->next;
	} else {
		p = vec->tail;
		for (i = vec->size - 1; i > index; i--)
			p = p->prev;
	}

	if (p == NULL)
		return -1;
	*item = p->data;
	return 0;
}

void vec_for_each(vec_t *vec, ds_callback_t cb, void *param)
{
	int i;
	vec_item_t *p;

	if (vec == NULL)
		return;

	p = vec->head;
	for (i = 0; i < vec->size; i++) {
		if (cb)
			cb(p->data, param);
		p = p->next;
	}
}

void vec_clear(vec_t *vec, ds_callback_t cb, void *param)
{
	int i;
	vec_item_t *p, *tmp;

	if (vec == NULL)
		return;

	p = vec->head;

	for (i = 0; i < vec->size; i++) {
		if (cb)
			cb(p->data, param);
		tmp = p;
		p = p->next;
		free(tmp);
	}

	vec->head = vec->tail = NULL;
	vec->size = 0;
}

void vec_destory(vec_t *vec, ds_callback_t cb, void *param)
{
	if (vec == NULL)
		return;

	vec_clear(vec, cb, param);
	free(vec);
}
