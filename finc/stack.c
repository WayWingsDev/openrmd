#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stk_t *stack_init()
{
	return vec_init();
}

inline int stack_push(stk_t *stack, void *data)
{
	return vec_push(stack, data);
}

inline int stack_pop(stk_t *stack, ds_callback_t cb, void *param)
{
	return vec_pop(stack, cb, param);
}

inline int stack_size(stk_t *stack)
{
	return vec_size(stack);
}

inline int stack_empty(stk_t *stack)
{
	return vec_empty(stack);
}

void stack_clear(stk_t *stack, ds_callback_t cb, void *param)
{
	vec_clear(stack, cb, param);
}

void stack_destory(stk_t *stack, ds_callback_t cb, void *param)
{
	vec_destory(stack, cb, param);
}
