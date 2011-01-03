#include <stdio.h>
#include <assert.h>
#include "_wpbintree.h"
#include "wpbase.h"

#define USE_JUMP_TABLE

#ifdef USE_JUMP_TABLE
typedef void (*wp_tree_node_dump_func)(const wp_tree_node_t *node, FILE *file, wp_write_func_t write_f, void *data);

wp_tree_node_dump_func action[] =
{
	wp_tree_node_dump,		/* BIN_TREE */
	rb_wp_tree_node_dump,	/* RB_TREE */
};

#endif /* USE_JUMP_TABLE */

wp_tree_node_t *_wp_bin_tree_new (void)
{
	return wp_tree_node_new_full (NULL, NULL, NULL, NULL);
}

void _wp_bin_tree_free (wp_tree_node_t *n, wp_tree_node_t *sent)
{
	assert (n != NULL);
	_wp_bin_tree_flush (n, sent);
}

void _wp_bin_tree_insert_left (wp_tree_node_t *p, wp_tree_node_t *l)
{
	assert (p != NULL);
	assert (l != NULL);
	
	wp_tree_node_set_left (p, l);
	wp_tree_node_set_parent (l, p);
}

void _wp_bin_tree_insert_right (wp_tree_node_t *p, wp_tree_node_t *r)
{
	assert (p != NULL);
	assert (r != NULL);

	wp_tree_node_set_right (p, r);
	wp_tree_node_set_parent (r, p);
}

int _wp_bin_tree_height (wp_tree_node_t *n, wp_tree_node_t *sent)
{
	int l, r;

	if (n == sent)
	{
		return 0;
	}

	l = _wp_bin_tree_height (wp_tree_node_get_left (n), sent);
	r = _wp_bin_tree_height (wp_tree_node_get_right (n), sent);

	return (WP_MAX (l, r) + 1);
}

wp_tree_node_t *_wp_bin_tree_search (wp_tree_node_t *n, wp_tree_node_t *sent, wp_compare_func_t f, void *data)
{
	int i;
	while ((n != sent) && ((i = f (data, wp_tree_node_get_content (n))) != 0))
	{
		if (i < 0)
		{
			n = wp_tree_node_get_left (n);
		}
		else
		{
			n = wp_tree_node_get_right (n);
		}
	}
	return n;
}

wp_tree_node_t *_wp_bin_tree_minimum (wp_tree_node_t *n, wp_tree_node_t *sent)
{
	wp_tree_node_t *tmp;
	while ((tmp = wp_tree_node_get_left (n)) != sent)
	{
		n = tmp;
	}
	return n;
}

wp_tree_node_t *_wp_bin_tree_maximum (wp_tree_node_t *n, wp_tree_node_t *sent)
{
	wp_tree_node_t *tmp;
	while ((tmp = wp_tree_node_get_right (n)) != sent)
	{
		n = tmp;
	}
	return n;
}

wp_tree_node_t *_wp_bin_tree_successor (wp_tree_node_t *n, wp_tree_node_t *sent)
{
	wp_tree_node_t *r;
	wp_tree_node_t *y;

	if ((r = wp_tree_node_get_right (n)) != sent)
	{
		return (_wp_bin_tree_minimum (r, sent));
	}

	y = wp_tree_node_get_parent (n);
	while ((y != sent) && (n == wp_tree_node_get_right (y)))
	{
		n = y;
		y = wp_tree_node_get_parent (y);
	}

	return y;
}
				
wp_tree_node_t *_wp_bin_tree_predecessor (wp_tree_node_t *n, wp_tree_node_t *sent)
{
	wp_tree_node_t *l;
	wp_tree_node_t *y;
	
	if ((l = wp_tree_node_get_left (n)) != sent)
	{
		return (_wp_bin_tree_maximum (l, sent));
	}

	y = wp_tree_node_get_parent (n);
	while ((y != sent) && (n == wp_tree_node_get_left (y)))
	{
		n = y;
		y = wp_tree_node_get_parent (y);
	}

	return y;
}

void _wp_bin_tree_map_prefix (wp_tree_node_t *n, wp_tree_node_t *sent, FILE *file, wp_write_func_t f, void *data)
{
	if (n != sent)
	{
		f (wp_tree_node_get_content (n), file, data);
		_wp_bin_tree_map_prefix (wp_tree_node_get_left (n), sent, file, f, data);
		_wp_bin_tree_map_prefix (wp_tree_node_get_right (n), sent, file, f, data);
	}
}

void _wp_bin_tree_map_infix (wp_tree_node_t *n, wp_tree_node_t *sent, FILE *file, wp_write_func_t f, void *data)
{
	if (n != sent)
	{
		_wp_bin_tree_map_infix (wp_tree_node_get_left (n), sent, file, f, data);
		f (wp_tree_node_get_content (n), file, data);
		_wp_bin_tree_map_infix (wp_tree_node_get_right (n), sent, file, f, data);
	}
}

void _wp_bin_tree_map_postfix (wp_tree_node_t *n, wp_tree_node_t *sent, FILE *file, wp_write_func_t f, void *data)
{
	if (n != sent)
	{
		_wp_bin_tree_map_postfix (wp_tree_node_get_left (n), sent, file, f, data);
		_wp_bin_tree_map_postfix (wp_tree_node_get_right (n), sent, file, f, data);
		f (wp_tree_node_get_content (n), file, data);
	}
}

void _wp_bin_tree_flush (wp_tree_node_t *n, wp_tree_node_t *sent)
{
	if (n != sent)
	{
		_wp_bin_tree_flush (wp_tree_node_get_left (n), sent);
		_wp_bin_tree_flush (wp_tree_node_get_right (n), sent);
		wp_tree_node_free (n);
	}
}

void _wp_bin_tree_dump (wp_tree_node_t *n, wp_tree_node_t *sent, FILE *file, wp_write_func_t f, void *data, wp_bin_tree_tType type)
{
	if (n != sent)
	{
		_wp_bin_tree_dump (wp_tree_node_get_left (n), sent, file, f, data, type);

#if defined USE_JUMP_TABLE
		action[type](n, file, f, data);
#else
		switch (type)
		{
			case BIN_TREE:
				wp_tree_node_dump (n, file, f, data);
				break;
			case RB_TREE:
				rb_wp_tree_node_dump (n, file, f, data);
				break;
			default:
				fprintf (stderr, "oops! not such tree\n");
				break;
		}
#endif /* USE_JUMP_TABLE */
		_wp_bin_tree_dump (wp_tree_node_get_right (n), sent, file, f, data, type);
	}
}

void _wp_bin_tree_foreach (wp_tree_node_t *n, wp_tree_node_t *sent, wp_foreach_func_t f, void *data)
{
	if (n != sent)
	{
		if (f (wp_tree_node_get_content, data) == false)
		{
			return;
		}
		_wp_bin_tree_foreach (wp_tree_node_get_left (n), sent, f, data);
		_wp_bin_tree_foreach (wp_tree_node_get_right (n), sent, f, data);
	}
}
