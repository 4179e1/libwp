#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdbool.h>
#include "wpbase.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _wp_stack wp_stack_t;

wp_stack_t *stack_new (int size);
void stack_free (wp_stack_t *s);
void stack_flush (wp_stack_t *s);

bool stack_is_empty (const wp_stack_t *s);
int stack_get_size (const wp_stack_t *s);
int stack_get_card (const wp_stack_t *s);
int stack_get_growing_factor (const wp_stack_t *s);
void stack_set_growing_factor (wp_stack_t *s, int value);

void stack_push (wp_stack_t *stack, void *data);
void *stack_pop (wp_stack_t *stack);
void *stack_top (const wp_stack_t *stack);

void stack_dump (const wp_stack_t *s, FILE *file, wp_write_func_t f, void *data);
void stack_foreach (const wp_stack_t *s, wp_foreach_func_t f, void *data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _STACK_H */
