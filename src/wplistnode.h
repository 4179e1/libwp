#ifndef _LISTNODE_H
#define _LISTNODE_H

#include <stdio.h>
#include "wpbase.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _wp_list_node wp_list_node_t;

wp_list_node_t *wp_list_node_new (void);
wp_list_node_t *wp_list_node_new_full (void *data, wp_list_node_t *p, wp_list_node_t *n);
void wp_list_node_free (wp_list_node_t *n);

void wp_list_node_set_content (wp_list_node_t *node, void *data);
void wp_list_node_set_next (wp_list_node_t *node, wp_list_node_t *next);
void wp_list_node_set_prev (wp_list_node_t *node, wp_list_node_t *prev);

void *wp_list_node_get_content (const wp_list_node_t *node);
wp_list_node_t *wp_list_node_get_next (const wp_list_node_t *node);
wp_list_node_t *wp_list_node_get_prev (const wp_list_node_t *node);

void wp_list_node_link (wp_list_node_t *prev, wp_list_node_t *next);
void wp_list_node_unlink (wp_list_node_t *prev, wp_list_node_t *next);

void wp_list_node_insert_before (wp_list_node_t *n, wp_list_node_t *prev);
void wp_list_node_insert_after (wp_list_node_t *n, wp_list_node_t *next);

void wp_list_node_dump (const wp_list_node_t *node, FILE *file, wp_write_func_t f, void *data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LIST_H */
