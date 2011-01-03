#ifndef _RBTREE_H
#define _RBTREE_H

#include <stdio.h>
#include "wpbase.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _wp_rbtree wp_rb_tree_t;

wp_rb_tree_t *wp_rb_tree_new (wp_compare_func_t cmp_f);
void wp_rb_tree_free (wp_rb_tree_t *t);
void wp_rb_tree_flush (wp_rb_tree_t *t);

bool wp_rb_tree_is_empty (const wp_rb_tree_t *t);
int wp_rb_tree_get_card (const wp_rb_tree_t *t);
int wp_rb_tree_get_height (const wp_rb_tree_t *t);

void *wp_rb_tree_get_root (const wp_rb_tree_t *t);
void *wp_rb_tree_get_minimum (const wp_rb_tree_t *t);
void *wp_rb_tree_get_maximum (const wp_rb_tree_t *t);

void wp_rb_tree_insert (wp_rb_tree_t *t, void *data);
void *wp_rb_tree_search (const wp_rb_tree_t *t, void *data);
void *wp_rb_tree_delete (wp_rb_tree_t *t, void *data);

void wp_rb_tree_map_prefix (const wp_rb_tree_t *t, FILE *file, wp_write_func_t f, void *data);
void wp_rb_tree_map_infix (const wp_rb_tree_t *t, FILE *file, wp_write_func_t f, void *data);
void wp_rb_tree_map_postfix (const wp_rb_tree_t *t, FILE *file, wp_write_func_t f, void *data);

void wp_rb_tree_dump (const wp_rb_tree_t *t, FILE *file, wp_write_func_t f, void *data);
void wp_rb_tree_foreach (wp_rb_tree_t *t, wp_foreach_func_t f, void *data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RBTREE_H */
