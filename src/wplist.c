#include <stdlib.h>
#include <wpmacros.h>
#include <wplist.h>
#include <wplistnode.h>

static wp_list_node_t *wp_list_search_node (wp_list_t *l, const void *data, wp_compare_func_t cmp_f);
static wp_list_node_t *wp_list_search_node_by_position (wp_list_t *l, int pos);
static wp_list_node_t *wp_list_merge_sort (wp_list_t *l, wp_list_node_t *u, wp_list_node_t *z, wp_compare_func_t cmp_f);
static wp_list_node_t *wp_list_merge (wp_list_t *l, wp_list_node_t *s, wp_list_node_t *t, wp_list_node_t *z, wp_compare_func_t cmp_f);

struct _wp_list
{
	wp_list_node_t *sent;
	wp_list_node_t *end;
	int card;
};

struct _wp_list_cursor
{
	wp_list_t *l;
	wp_list_node_t *n;
};

wp_list_t *wp_list_new (void)
{
	wp_list_t *l;

	l = (wp_list_t *)malloc (sizeof (wp_list_t));
	if (l == NULL)
	{
		return NULL;
	}
	
	l->sent = wp_list_node_new ();
	if (l->sent == NULL)
	{
		free (l);
		return NULL;
	}

	l->end = wp_list_node_new ();
	if (l->end == NULL)
	{
		free (l->sent);
		free (l);
		return NULL;
	}

	
	wp_list_node_link (l->sent, l->end);
	wp_list_node_set_prev (l->sent, l->sent);
	wp_list_node_set_next (l->end, l->end);

	l->card = 0;

	return l;
}

void wp_list_free (wp_list_t *l)
{
	wp_return_if_fail (l != NULL);
	wp_list_flush (l);
	free (l->sent);
	free (l->end);
	free (l);
}

void wp_list_flush (wp_list_t *l)
{
	wp_list_node_t *tmp;
	wp_list_node_t *save;

	wp_return_if_fail (l != NULL);

	tmp = wp_list_node_get_next (l->sent); 
	while (tmp != l->end)
	{
		save = tmp;
 		tmp = wp_list_node_get_next (tmp);
		wp_list_node_free (save);
	}

	wp_list_node_link (l->sent, l->end);
	l->card = 0;
}

int wp_list_is_empty (wp_list_t *l)
{
	wp_return_val_if_fail (l != NULL, -1);
	return (l->card == 0);
}

int wp_list_get_card (wp_list_t *l)
{
	wp_return_val_if_fail (l != NULL, -1);
	return l->card;
}

void wp_list_insert_head (wp_list_t *l, void *data)
{
	wp_list_node_t *node;

	wp_return_if_fail (l != NULL);

	node = wp_list_node_new ();
	if (node == NULL)
	{
		return;
	}
	wp_list_node_set_content (node, data);

	wp_list_node_link (node, wp_list_node_get_next (l->sent));
	wp_list_node_link (l->sent, node);

	(l->card)++;
}

void wp_list_insert_tail (wp_list_t *l, void *data)
{
	wp_list_node_t *node;

	wp_return_if_fail (l != NULL);

	node = wp_list_node_new ();
	if (node == NULL)
	{
		return;
	}
	wp_list_node_set_content (node, data);

	wp_list_node_link (wp_list_node_get_prev (l->end), node);
	wp_list_node_link (node, l->end);

	(l->card)++;
}

void *wp_list_head (wp_list_t *l)
{
	wp_return_val_if_fail (l != NULL, NULL);
	return wp_list_node_get_content (wp_list_node_get_next (l->sent));
}

void *wp_list_tail (wp_list_t *l)
{
	wp_return_val_if_fail (l != NULL, NULL);
	return wp_list_node_get_content (wp_list_node_get_prev (l->end));
}

void *wp_list_delete_head (wp_list_t *l)
{
	wp_list_node_t *head;
	wp_list_node_t *tmp;
	void *data;

	wp_return_val_if_fail (l != NULL, NULL);

	head = wp_list_node_get_next (l->sent);
	tmp = wp_list_node_get_next (head);

	wp_list_node_link (l->sent, tmp);
	(l->card)--;

	data = wp_list_node_get_content (head);
	wp_list_node_free (head);
	return data;
}

void *wp_list_delete_tail (wp_list_t *l)
{
	wp_list_node_t *tail;
	wp_list_node_t *tmp;
	void *data;

	wp_return_val_if_fail (l != NULL, NULL);

	tail = wp_list_node_get_prev (l->end);
	tmp = wp_list_node_get_prev (tail);

	wp_list_node_link (tail, tmp);
	(l->card)--;

	data = wp_list_node_get_content (tail);
	wp_list_node_free (tail);
	return tail;
}

void *wp_list_delete (wp_list_t *l, const void *data, wp_compare_func_t cmp_f)
{
	wp_list_node_t *tmp;
	void *rt;

	wp_return_val_if_fail (l != NULL, NULL);
	wp_return_val_if_fail (cmp_f != NULL, NULL);
	
	for (tmp = wp_list_node_get_next (l->sent); tmp != l->end; tmp = wp_list_node_get_next (tmp))
	{
		if (cmp_f (wp_list_node_get_content (tmp), data) == 0)
		{
			/* found */
			wp_list_node_link (wp_list_node_get_prev (tmp), wp_list_node_get_next (tmp));
			(l->card)--;

			rt = wp_list_node_get_content (tmp);
			wp_list_node_free (tmp);
			return rt;
		}
	}

	return NULL;
}

void *wp_list_search (wp_list_t *l, const void *data, wp_compare_func_t cmp_f)
{
	wp_list_node_t *tmp;

	wp_return_val_if_fail (l != NULL, NULL);
	wp_return_val_if_fail (cmp_f != NULL, NULL);

	tmp = wp_list_search_node (l, data, cmp_f);
	if (tmp == NULL)
	{
		return NULL;
	}

	return wp_list_node_get_content (tmp);
}


void *wp_list_search_by_position (wp_list_t *l, int pos)
{
	wp_list_node_t *node;

	wp_return_val_if_fail (l != NULL, NULL);

	node = wp_list_search_node_by_position (l, pos);
	if (node == NULL)
	{
		return NULL;
	}

	return wp_list_node_get_content (node);
}

void *wp_list_search_max (wp_list_t *l, wp_compare_func_t cmp_f)
{
	wp_list_node_t *max;
	wp_list_node_t *tmp;

	wp_return_val_if_fail (l != NULL, NULL);
	wp_return_val_if_fail (cmp_f != NULL, NULL);

	max = wp_list_node_get_next (l->sent);
	for (tmp = wp_list_node_get_next (max); tmp != l->end; tmp = wp_list_node_get_next (tmp))
	{
		if (cmp_f (wp_list_node_get_content (tmp), wp_list_node_get_content (max)) > 0)
		{
			max = tmp;
		}
	}

	if (max == l->end)
	{
		return NULL;
	}

	return wp_list_node_get_content (max);
}

void *wp_list_search_min (wp_list_t *l, wp_compare_func_t cmp_f)
{
	wp_list_node_t *min;
	wp_list_node_t *tmp;

	wp_return_val_if_fail (l != NULL, NULL);
	wp_return_val_if_fail (cmp_f != NULL, NULL);

	if (l->card == 0)
	{
		fprintf (stderr, "wp_list_t is empty\n");
		return NULL;
	}

	min = wp_list_node_get_next (l->sent);
	for (tmp = wp_list_node_get_next (min); tmp != l->end; tmp = wp_list_node_get_next (tmp))
	{
		if (cmp_f (wp_list_node_get_content (tmp), wp_list_node_get_content (min)) < 0)
		{
			min = tmp;
		}
	}

	if (min == l->end)
	{
		return NULL;
	}

	return wp_list_node_get_content (min);
}

void wp_list_sort (wp_list_t *l, wp_compare_func_t cmp_f)
{
	wp_return_if_fail (l != NULL);
	wp_return_if_fail (cmp_f != NULL);

	wp_list_node_link (l->sent, wp_list_merge_sort (l, wp_list_node_get_next (l->sent), l->end, cmp_f));
}

void wp_list_dump (wp_list_t *l, FILE *file, wp_write_func_t f, void *data)
{
	wp_list_node_t *node;
	wp_return_if_fail (l != NULL);
	wp_return_if_fail (file != NULL);

	fprintf (file, "<LIST REF=\"%p\" CARD=\"%d\" SENT=\"%p\" END=\"%p\">", (void *)l, l->card, (void *)l->sent, (void *)l->end);
	for (node = wp_list_node_get_next (l->sent); node != l->end; node = wp_list_node_get_next (node))
	{
		wp_list_node_dump (node, file, f, data);
	}
	fprintf (file, "</LIST>\n");
}

void wp_list_foreach (wp_list_t *l, wp_foreach_func_t f, void *data)
{
	wp_list_node_t *node;
	wp_return_if_fail (l != NULL);
	wp_return_if_fail (f != NULL);

	for (node = wp_list_node_get_next (l->sent); node != l->end; node = wp_list_node_get_next (node))
	{
		if (f (wp_list_node_get_content (node), data) == false)
		{
			break;
		}
	}
}

/* wp_list_t Cursor */
wp_list_cursor_t *wp_list_cursor_new (wp_list_t *l)
{
	wp_list_cursor_t *lc;

	wp_return_val_if_fail (l != NULL, NULL);

	lc = (wp_list_cursor_t *)malloc (sizeof (wp_list_cursor_t));
	if (lc == NULL)
	{
		return NULL;
	}

	lc->l = l;
	lc->n = wp_list_node_get_next (l->sent);

	return lc;
}

void wp_list_cursor_free (wp_list_cursor_t *lc)
{
	wp_return_if_fail (lc != NULL);

	free (lc);
}

int wp_list_cursor_is_head (const wp_list_cursor_t *lc)
{
	wp_return_val_if_fail (lc != NULL, -1);

	if (wp_list_is_empty (lc->l))
	{
		return false;
	}

	return (lc->n == wp_list_node_get_next (lc->l->sent));
}

int wp_list_cursor_is_tail (const wp_list_cursor_t *lc)
{
	wp_return_val_if_fail (lc != NULL, -1);
	if (wp_list_is_empty (lc->l))
	{
		return false;
	}

	return (lc->n == wp_list_node_get_prev (lc->l->end));
}
			
void wp_list_cursor_move_to_head (wp_list_cursor_t *lc)
{
	wp_return_if_fail (lc != NULL);

	lc->n = wp_list_node_get_next (lc->l->sent);
}

void wp_list_cursor_move_to_tail (wp_list_cursor_t *lc)
{
	wp_return_if_fail (lc != NULL);

	lc->n = wp_list_node_get_prev (lc->l->end);
}

void wp_list_cursor_step_forward (wp_list_cursor_t *lc)
{
	wp_return_if_fail (lc != NULL);

	lc->n = wp_list_node_get_next (lc->n);
}

void wp_list_cursor_step_backward (wp_list_cursor_t *lc)
{
	wp_return_if_fail (lc != NULL);

	lc->n = wp_list_node_get_prev (lc->n);
}

void *wp_list_cursor_move_to_value (wp_list_cursor_t *lc, void *value, wp_compare_func_t cmp_f)
{
	wp_list_node_t *n;

	wp_return_val_if_fail (lc != NULL, NULL);

	n = wp_list_search_node (lc->l, value, cmp_f);

	if (n == NULL)
	{
		return NULL;
	}

	lc->n = n;
	return wp_list_node_get_content (n);
}

void *wp_list_cursor_move_to_position (wp_list_cursor_t *lc, int pos)
{
	wp_list_node_t *n;

	wp_return_val_if_fail (lc != NULL, NULL);

	n = wp_list_search_node_by_position (lc->l, pos);

	if (n == NULL)
	{
		return NULL;
	}

	lc->n = n;
	return wp_list_node_get_content (n);
}

void wp_list_cursor_set_content (wp_list_cursor_t *lc, void *data)
{
	wp_return_if_fail (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return;
	}

	wp_list_node_set_content (lc->n ,data);
}

void *wp_list_cursor_get_content (wp_list_cursor_t *lc)
{
	wp_return_val_if_fail (lc != NULL, NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return NULL;
	}

	return wp_list_node_get_content (lc->n);
}

void wp_list_cursor_insert_before (wp_list_cursor_t *lc, void *data)
{
	wp_list_node_t *tmp;

	wp_return_if_fail (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return;
	}

	tmp = wp_list_node_new_full (data, NULL, NULL);
	if (tmp == NULL)
	{
		return;
	}

	wp_list_node_insert_before (lc->n, tmp);
	(lc->l->card)++;
}
	
void wp_list_cursor_insert_after (wp_list_cursor_t *lc, void *data)
{
	wp_list_node_t *tmp;

	wp_return_if_fail (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return;
	}

	tmp = wp_list_node_new_full (data, NULL, NULL);
	if (tmp == NULL)
	{
		return;
	}

	wp_list_node_insert_after (lc->n, tmp);
	(lc->l->card)++;
}

void *wp_list_cursor_remove (wp_list_cursor_t *lc)
{
	wp_list_node_t *p;
	wp_list_node_t *n;
	void *data;

	wp_return_val_if_fail (lc != NULL, NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return NULL;
	}

	n = wp_list_node_get_next (lc->n);
	if (n == lc->l->end)
	{
		return NULL;
	}
	p = wp_list_node_get_prev (lc->n);

	data = wp_list_node_get_content (lc->n);
	wp_list_node_free (lc->n);
	wp_list_node_link (p, n);
	(lc->l->card)--;
	
	lc->n = n;

	return data;
}

void *wp_list_cursor_remove_before (wp_list_cursor_t *lc)
{
	wp_list_node_t *tmp;
	wp_list_node_t *p;
	void *data;

	wp_return_val_if_fail (lc != NULL, NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return NULL;
	}

	tmp = wp_list_node_get_prev (lc->n);
	if (tmp == lc->l->sent)
	{
		return NULL;
	}

	p = wp_list_node_get_prev (tmp);
	data = wp_list_node_get_content (tmp);
	wp_list_node_free (tmp);
	wp_list_node_link (p, lc->n);
	(lc->l->card)--;

	return data;
}
	
void *wp_list_cursor_remove_after (wp_list_cursor_t *lc)
{
	wp_list_node_t *tmp;
	wp_list_node_t *n;
	void *data;
	
	wp_return_val_if_fail (lc != NULL, NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return NULL;
	}

	tmp = wp_list_node_get_next (lc->n);
	if (tmp == lc->l->end)
	{
		return NULL;
	}

	n = wp_list_node_get_next (tmp);
	data = wp_list_node_get_content (tmp);
	wp_list_node_free (tmp);
	wp_list_node_link (lc->n, n);
	(lc->l->card)--;

	return data;
}

/* private func */
static wp_list_node_t *wp_list_search_node (wp_list_t *l, const void *data, wp_compare_func_t cmp_f)
{
	wp_list_node_t *tmp;

	for (tmp = wp_list_node_get_next (l->sent); tmp != l->end; tmp = wp_list_node_get_next (tmp))
	{
		if (cmp_f (wp_list_node_get_content (tmp), data) == 0)
		{
			return tmp;
		}
	}

	return NULL;
}

static wp_list_node_t *wp_list_search_node_by_position (wp_list_t *l, int pos)
{
	wp_list_node_t *node;	
	int i;

	if (pos < 0 || pos >= (l->card))
	{
		return NULL;
	}

	node = wp_list_node_get_next (l->sent);
	for (i = 0; i < pos; i++)
	{
		node = wp_list_node_get_next (node);
	}

	return node;
}

static wp_list_node_t *wp_list_merge_sort (wp_list_t *l, wp_list_node_t *u, wp_list_node_t *z, wp_compare_func_t cmp_f)
{
	wp_list_node_t *s;
	wp_list_node_t *t;

	if (wp_list_node_get_next (u) == z)
	{
		return u;
	}

	s = u;
	t = wp_list_node_get_next (wp_list_node_get_next (wp_list_node_get_next (u)));
	/* t run twice faster than u, when t meet z, u is at the middle of the wp_list */
	while (t != z)
	{
		u = wp_list_node_get_next (u);
		t = wp_list_node_get_next (wp_list_node_get_next (t));
	}

	/* so we link two sub-list to z */
	t = wp_list_node_get_next (u);
	wp_list_node_set_next (u, z);

	return wp_list_merge (l, wp_list_merge_sort (l, s, z, cmp_f), wp_list_merge_sort (l, t, z, cmp_f), l->end, cmp_f);
}

static wp_list_node_t *wp_list_merge (wp_list_t *l, wp_list_node_t *s, wp_list_node_t *t, wp_list_node_t *z, wp_compare_func_t cmp_f)
{
	/* 
	 * the node u is the last element of the new wp_list begin from z
	 * s------->
	 *          z------>u
	 * t------->
	 */
	wp_list_node_t *u = z;

	do {
		if (t == z)
		{
			wp_list_node_link (u, s);
			u = s;
			s = wp_list_node_get_next (s);
			continue;
		}

		if (s == z)
		{
			wp_list_node_link (u, t);
			u = t;
			t = wp_list_node_get_next (t);
			continue;
		}

		if (cmp_f (wp_list_node_get_content (s), wp_list_node_get_content (t)) <= 0)
		{
			wp_list_node_link (u, s);
			u = s;
			s = wp_list_node_get_next (s);
		}
		else
		{
			wp_list_node_link (u, t);
			u = t;
			t = wp_list_node_get_next (t);
		}
	} while (u != z);

	/* now u is the begining of wp_list, and we fix the broken sentinal z */
	u = wp_list_node_get_next (z);
	wp_list_node_set_next (z, z);

	return u;
}
