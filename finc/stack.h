#ifndef _STACK_H_
#define _STACK_H_

#include "ds_comm.h"
#include "vector.h"

/* stack type */
typedef vec_t stk_t;

/* initialize a new stack */
stk_t *stack_init();

/* add a node into stack tail, return 0 if success or -1 if failed */
inline int stack_push(stk_t *stack, void *data);

/* delete a node from stack tail */
inline int stack_pop(stk_t *stack, ds_callback_t cb, void *param);

/* return the items number in stack */
inline int stack_size(stk_t *stack);

/* return 1(TRUE) if stack is empty. Otherwise, return 0(FALSE). */
inline int stack_empty(stk_t *stack);

/* delete all node in stack */
void stack_clear(stk_t *stack, ds_callback_t cb, void *param);

/* free a stack */
void stack_destory(stk_t *stack, ds_callback_t cb, void *param);

#endif	/* _STACK_H_ */
