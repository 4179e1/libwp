#ifndef _LIST_H
#define _LIST_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdio.h>
#include "wpbase.h"

typedef struct _wp_list wp_list_t;

typedef struct _wp_list_cursor wp_list_cursor_t;

wp_list_t *wp_list_new (void);
void wp_list_free (wp_list_t *l);
void wp_list_flush (wp_list_t *l);

bool wp_list_is_empty (wp_list_t *l);
int wp_list_get_card (wp_list_t *l);

void wp_list_insert_head (wp_list_t *l, void *data);
void wp_list_insert_tail (wp_list_t *l, void *data);

void *wp_list_head (wp_list_t *l);
void *wp_list_tail (wp_list_t *l);

void *wp_list_delete_head (wp_list_t *l);
void *wp_list_delete_tail (wp_list_t *l);
void *wp_list_delete (wp_list_t *l, const void *data, wp_compare_func_t cmp_f);

void *wp_list_search (wp_list_t *l, const void *data, wp_compare_func_t cmp_f);
/* postition begin from 0 */
void *wp_list_search_by_position (wp_list_t *l, int pos);
void *wp_list_search_max (wp_list_t *l, wp_compare_func_t cmp_f);
void *wp_list_search_min (wp_list_t *l, wp_compare_func_t cmp_f);

void wp_list_sort (wp_list_t *l, wp_compare_func_t cmp_f);

void wp_list_dump (wp_list_t *l, FILE *file, wp_write_func_t f, void *data);
void wp_list_foreach (wp_list_t *l, wp_foreach_func_t f, void *data);

/* wp_list_t Cursor */
wp_list_cursor_t *wp_list_cursor_new (wp_list_t *l);
void wp_list_cursor_free (wp_list_cursor_t *lc);

bool wp_list_cursor_is_head (const wp_list_cursor_t *lc);
bool wp_list_cursor_is_tail (const wp_list_cursor_t *lc);

void wp_list_cursor_move_to_head (wp_list_cursor_t *lc);
void wp_list_cursor_move_to_tail (wp_list_cursor_t *lc);
void wp_list_cursor_step_forward (wp_list_cursor_t *lc);
void wp_list_cursor_step_backward (wp_list_cursor_t *lc);
void *wp_list_cursor_move_to_value (wp_list_cursor_t *lc, void *value, wp_compare_func_t cmp_f);
void *wp_list_cursor_move_to_position (wp_list_cursor_t *lc, int i);

void wp_list_cursor_set_content (wp_list_cursor_t *lc, void *data);
void *wp_list_cursor_get_content (wp_list_cursor_t *lc);

void wp_list_cursor_insert_before (wp_list_cursor_t *lc, void *data);
void wp_list_cursor_insert_after (wp_list_cursor_t *lc, void *data);
void *wp_list_cursor_remove (wp_list_cursor_t *lc);
void *wp_list_cursor_remove_before (wp_list_cursor_t *lc);
void *wp_list_cursor_remove_after (wp_list_cursor_t *lc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LIST_H */
