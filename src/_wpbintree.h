#ifndef __WP_BINTREE_H
#define __WP_BINTREE_H

#include <stdio.h>
#include <wptreenode.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


typedef enum _wp_bin_tree_type
{
	BIN_TREE = 0,
	RB_TREE,
} wp_bin_tree_tType;

wp_tree_node_t *_wp_bin_tree_new (void);
void _wp_bin_tree_free (wp_tree_node_t *n, wp_tree_node_t *sent);

void _wp_bin_tree_insert_left (wp_tree_node_t *p, wp_tree_node_t *l);
void _wp_bin_tree_insert_right (wp_tree_node_t *p, wp_tree_node_t *r);

int _wp_bin_tree_height (wp_tree_node_t *n, wp_tree_node_t *sent);
wp_tree_node_t *_wp_bin_tree_search (wp_tree_node_t *n, wp_tree_node_t *sent, wp_compare_func_t f, void *data);

wp_tree_node_t *_wp_bin_tree_minimum (wp_tree_node_t *n, wp_tree_node_t *sent);
wp_tree_node_t *_wp_bin_tree_maximum (wp_tree_node_t *n, wp_tree_node_t *sent);

wp_tree_node_t *_wp_bin_tree_successor (wp_tree_node_t *n, wp_tree_node_t *sent);
wp_tree_node_t *_wp_bin_tree_predecessor (wp_tree_node_t *n, wp_tree_node_t *sent);

void _wp_bin_tree_map_prefix (wp_tree_node_t *n, wp_tree_node_t *sent, FILE *file, wp_write_func_t f, void *data);
void _wp_bin_tree_map_infix (wp_tree_node_t *n, wp_tree_node_t *sent, FILE *file, wp_write_func_t f, void *data);
void _wp_bin_tree_map_postfix (wp_tree_node_t *n, wp_tree_node_t *sent, FILE *file, wp_write_func_t f, void *data);

void _wp_bin_tree_flush (wp_tree_node_t *n, wp_tree_node_t *sent);
void _wp_bin_tree_dump (wp_tree_node_t *n, wp_tree_node_t *sent, FILE *file, wp_write_func_t f, void *data, wp_bin_tree_tType type);
void _wp_bin_tree_foreach (wp_tree_node_t *n, wp_tree_node_t *sent, wp_foreach_func_t f, void *data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WP_BINTREE_H */
