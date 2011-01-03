#ifndef _BINTREE_H
#define _BINTREE_H

#include <stdio.h>
#include <stdbool.h>
#include "wpbase.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _wp_bintree wp_bin_tree_t;

wp_bin_tree_t *wp_bin_tree_new (wp_compare_func_t cmp_f);
void wp_bin_tree_free (wp_bin_tree_t *t);
void wp_bin_tree_flush (wp_bin_tree_t *t);

bool wp_bin_tree_is_empty (const wp_bin_tree_t *t);
int wp_bin_tree_get_card (const wp_bin_tree_t *t);
int wp_bin_tree_get_height (const wp_bin_tree_t *t);

void *wp_bin_tree_get_root (const wp_bin_tree_t *t);
void *wp_bin_tree_get_minimum (const wp_bin_tree_t *t);
void *wp_bin_tree_get_maximum (const wp_bin_tree_t *t);

void wp_bin_tree_insert (wp_bin_tree_t *t, void *data);
void *wp_bin_tree_search (const wp_bin_tree_t *t, void *data);
void *wp_bin_tree_delete (wp_bin_tree_t *t, void *data);

void wp_bin_tree_map_prefix (const wp_bin_tree_t *t, FILE *file, wp_write_func_t f, void *data);
void wp_bin_tree_map_infix (const wp_bin_tree_t *t, FILE *file, wp_write_func_t f, void *data);
void wp_bin_tree_map_postfix (const wp_bin_tree_t *t, FILE *file, wp_write_func_t f, void *data);

void wp_bin_tree_dump (const wp_bin_tree_t *t, FILE *file, wp_write_func_t f, void *data);
void wp_bin_tree_foreach (wp_bin_tree_t *t, wp_foreach_func_t f, void *data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BINTREE_H */
