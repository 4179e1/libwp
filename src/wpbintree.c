#include <assert.h>
#include <stdlib.h>
#include "_wpbintree.h"
#include "wpbintree.h"
#include "wptreenode.h"

struct _wp_bintree
{
	wp_tree_node_t *sent;
	int card;
	wp_compare_func_t cmp_f;
};

wp_bin_tree_t *wp_bin_tree_new (wp_compare_func_t cmp_f)
{
	wp_bin_tree_t *t;

	assert (cmp_f != NULL);

	t = (wp_bin_tree_t *)malloc (sizeof (wp_bin_tree_t));
	if (t == NULL)
	{
		return NULL;
	}

	t->sent = wp_tree_node_new_full (NULL, NULL, NULL, NULL);
	if (t->sent == NULL)
	{
		free (t);
		return NULL;
	}

	t->card = 0;
	t->cmp_f = cmp_f;

	return t;
}

void wp_bin_tree_free (wp_bin_tree_t *t)
{
	assert (t != NULL);

	wp_bin_tree_flush (t);
	free (t->sent);
	free (t);
}

void wp_bin_tree_flush (wp_bin_tree_t *t)
{
	assert (t != NULL);

	_wp_bin_tree_flush (wp_tree_node_get_right (t->sent), NULL);
	wp_tree_node_set_right (t->sent, NULL);
	t->card = 0;
}

bool wp_bin_tree_is_empty (const wp_bin_tree_t *t)
{
	assert (t != NULL);
	return (t->card == 0);
}

int wp_bin_tree_get_card (const wp_bin_tree_t *t)
{
	assert (t != NULL);
	return t->card;
}

int wp_bin_tree_get_height (const wp_bin_tree_t *t)
{
	assert (t != NULL);

	return _wp_bin_tree_height (wp_tree_node_get_right (t->sent), NULL);
}

void *wp_bin_tree_get_root (const wp_bin_tree_t *t)
{
	assert (t != NULL);

	return wp_tree_node_get_content (wp_tree_node_get_right (t->sent));
}

void *wp_bin_tree_get_minimum (const wp_bin_tree_t *t)
{
	assert (t != NULL);

	return wp_tree_node_get_content (_wp_bin_tree_minimum (wp_tree_node_get_right (t->sent), NULL));
}

void *wp_bin_tree_get_maximum (const wp_bin_tree_t *t)
{
	assert (t != NULL);

	return wp_tree_node_get_content (_wp_bin_tree_maximum (wp_tree_node_get_right (t->sent), NULL));
}

void wp_bin_tree_insert (wp_bin_tree_t *t, void *data)
{
	wp_tree_node_t *y;
	wp_tree_node_t *x;
	wp_tree_node_t *tmp;

	assert (t != NULL);

	tmp = wp_tree_node_new_full (data, NULL, NULL, NULL);
	if (tmp == NULL)
	{
		return;
	}

	y = NULL;
	x = wp_tree_node_get_right (t->sent);

	while (x != NULL)
	{
		y = x;
		if (t->cmp_f (data, wp_tree_node_get_content (x)) < 0)
		{
			x = wp_tree_node_get_left (x);
		}
		else
		{
			x = wp_tree_node_get_right (x);
		}
	}

	wp_tree_node_set_parent (tmp, y);

	if (y == NULL)
	{
		wp_tree_node_set_right (t->sent, tmp);	/* t is empty */
	}
	else
	{
		if (t->cmp_f (data, wp_tree_node_get_content (y)) < 0)
		{
			wp_tree_node_set_left (y, tmp);
		}
		else
		{
			wp_tree_node_set_right (y, tmp);
		}
	}

	(t->card)++;
}

void *wp_bin_tree_search (const wp_bin_tree_t *t, void *data)
{
	wp_tree_node_t *tmp;
	assert (t != NULL);

	tmp = _wp_bin_tree_search (wp_tree_node_get_right (t->sent), NULL, t->cmp_f, data);

	if (tmp == NULL)
	{
		return NULL;
	}

	return wp_tree_node_get_content (tmp);
}

void *wp_bin_tree_delete (wp_bin_tree_t *t, void *data)
{
	wp_tree_node_t *x;	/* y's not NULL child, or NULL if y don't have child */
	wp_tree_node_t *y;	/* the node actually delete */
	wp_tree_node_t *z;	/* the node contain data */
	wp_tree_node_t *py;	/* parent of y */

	assert (t != NULL);

	z = _wp_bin_tree_search (wp_tree_node_get_right (t->sent), NULL, t->cmp_f, data);
	if (z == NULL)
	{
		return NULL;
	}

	if ((wp_tree_node_get_left (z) == NULL) || (wp_tree_node_get_right (z) == NULL))
	{
		y = z;
	}
	else
	{
		y = _wp_bin_tree_successor (z, NULL);
	}

	if (wp_tree_node_get_left (y) != NULL)
	{
		x = wp_tree_node_get_left (y);
	}
	else
	{
		x = wp_tree_node_get_right (y);
	}

	py = wp_tree_node_get_parent (y);

	if (x != NULL)
	{
		wp_tree_node_set_parent (x, py);
	}

	if (py == NULL)
	{
		wp_tree_node_set_right (t->sent, x);
	}
	else
	{
		if (y == wp_tree_node_get_left (py))
		{
			wp_tree_node_set_left (py, x);
		}
		else
		{
			wp_tree_node_set_right (py, x);
		}
	}

	if (y != z)
	{
		wp_tree_node_set_content (z, wp_tree_node_get_content (y));
	}

	wp_tree_node_free (y);
	(t->card)--; 

	return data;
}

void wp_bin_tree_map_prefix (const wp_bin_tree_t *t, FILE *file, wp_write_func_t f, void *data)
{
	assert (t != NULL);
	assert (f != NULL);
	assert (file != NULL);
	_wp_bin_tree_map_prefix (wp_tree_node_get_right (t->sent), NULL, file, f, data);
}

void wp_bin_tree_map_infix (const wp_bin_tree_t *t, FILE *file, wp_write_func_t f, void *data)
{
	assert (t != NULL);
	assert (f != NULL);
	assert (file != NULL);
	_wp_bin_tree_map_infix (wp_tree_node_get_right (t->sent), NULL, file, f, data);
}
	
void wp_bin_tree_map_postfix (const wp_bin_tree_t *t, FILE *file, wp_write_func_t f, void *data)
{
	assert (t != NULL);
	assert (f != NULL);
	assert (file != NULL);
	_wp_bin_tree_map_postfix (wp_tree_node_get_right (t->sent), NULL, file, f, data);
}


void wp_bin_tree_dump (const wp_bin_tree_t *t, FILE *file, wp_write_func_t f, void *data)
{
	assert (t != NULL);
	assert (file != NULL);
	fprintf (file, "<BIN_TREE REF=\"%p\" CARD=\"%d\" SENT=\"%p\">", (void *)t, t->card, (void *)(t->sent));

	_wp_bin_tree_dump (wp_tree_node_get_right (t->sent), NULL, file, f, data, BIN_TREE);

	fprintf (file, "</BIN_TREE>\n");
}

void wp_bin_tree_foreach (wp_bin_tree_t *t, wp_foreach_func_t f, void *data)
{
	assert (t != NULL);
	assert (f != NULL);
	_wp_bin_tree_foreach (wp_tree_node_get_right (t->sent), NULL, f, data);
}
