#ifndef _TREENODE_H
#define _TREENODE_H

#include <stdio.h>
#include <stdbool.h>
#include <wptypes.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _wp_treenode wp_tree_node_t;

typedef enum _rb_wp_tree_node_cloor
{
	RB_TREE_RED = 0,
	RB_TREE_BLACK,
} wp_rb_tree_node_color_t;

wp_tree_node_t *wp_tree_node_new (void);
wp_tree_node_t *wp_tree_node_new_full (void *content, wp_tree_node_t *parent, wp_tree_node_t *left, wp_tree_node_t *right);
void wp_tree_node_copy (wp_tree_node_t *dest, const wp_tree_node_t *src);
void wp_tree_node_free (wp_tree_node_t *node);

void wp_tree_node_set_content (wp_tree_node_t *node, void *data);
void wp_tree_node_set_parent (wp_tree_node_t *node, wp_tree_node_t *parent);
void wp_tree_node_set_left (wp_tree_node_t *node, wp_tree_node_t *left);
void wp_tree_node_set_right (wp_tree_node_t *node, wp_tree_node_t *right);

void *wp_tree_node_get_content (const wp_tree_node_t *node);
wp_tree_node_t *wp_tree_node_get_parent (const wp_tree_node_t *node);
wp_tree_node_t *wp_tree_node_get_left (const wp_tree_node_t *node);
wp_tree_node_t *wp_tree_node_get_right (const wp_tree_node_t *node);

int wp_tree_node_is_leaf (const wp_tree_node_t *node);
int wp_tree_node_is_root (const wp_tree_node_t *node);

void wp_tree_node_dump (const wp_tree_node_t *node, FILE *file, wp_write_func_t f, void *data);

/* For Red-Black Tree */
void wp_tree_node_set_red (wp_tree_node_t *node);
void wp_tree_node_set_black (wp_tree_node_t *node);
int wp_tree_node_is_red (const wp_tree_node_t *node);
int wp_tree_node_is_black (const wp_tree_node_t *node);
wp_rb_tree_node_color_t wp_tree_node_get_color (const wp_tree_node_t *node);
void wp_tree_node_set_color (wp_tree_node_t *node, wp_rb_tree_node_color_t color);
void wp_tree_node_copy_color (wp_tree_node_t *dest, const wp_tree_node_t *src);
void rb_wp_tree_node_dump (const wp_tree_node_t *node, FILE *file, wp_write_func_t f, void *data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TREENODE_H */
