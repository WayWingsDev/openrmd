#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "ds_comm.h"

/* vector type */
typedef struct vec_t vec_t;

/* initialize a new vector */
vec_t *vec_init();

/* add a item into vector tail, return 0 if success or -1 if failed */
int vec_push(vec_t *vec, void *data);

/* delete a item from vector tail */
int vec_pop(vec_t *vec, ds_callback_t cb, void *param);

/* return the items number in vector */
int vec_size(vec_t *vec);

/* return 1(TRUE) if vector is empty. Otherwise, return 0(FALSE). */
int vec_empty(vec_t *vec);

/* get a item(data) from vector, return 0 if success or -1 if failed */
int vec_entry(vec_t *vec, int index, void **item);

void vec_for_each(vec_t *vec, ds_callback_t cb, void *param);

/* delete all items in vector */
void vec_clear(vec_t *vec, ds_callback_t cb, void *param);

/* free a vector */
void vec_destory(vec_t *vec, ds_callback_t cb, void *param);

#endif	/* _VECTOR_H_ */
