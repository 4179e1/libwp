#include <assert.h>
#include <stdlib.h>
#include <wptreenode.h>
#include <_wpbintree.h>
#include <wprbtree.h>

#define TREE_ROOT(T) (wp_tree_node_get_right (T->sent))

static void left_rotate (wp_rb_tree_t *t, wp_tree_node_t *x);
static void right_rotate (wp_rb_tree_t *t, wp_tree_node_t *x);
static void rb_insert_fixup (wp_rb_tree_t *t, wp_tree_node_t *z);
static void rb_delete_fixup (wp_rb_tree_t *t, wp_tree_node_t *x);

struct _wp_rbtree
{
	wp_tree_node_t *sent;
	int card;
	wp_compare_func_t cmp_f;
};

wp_rb_tree_t *wp_rb_tree_new (wp_compare_func_t cmp_f)
{
	wp_rb_tree_t *t;

	assert (cmp_f != NULL);
	
	t = (wp_rb_tree_t *) malloc (sizeof (wp_rb_tree_t));
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
	wp_tree_node_set_right (t->sent, t->sent);
	wp_tree_node_set_black (t->sent);

	t->card = 0;
	t->cmp_f = cmp_f;

	return t;
}

void wp_rb_tree_free (wp_rb_tree_t *t)
{
	assert (t != NULL);
	wp_rb_tree_flush (t);
	free (t->sent);
	free (t);
}

void wp_rb_tree_flush (wp_rb_tree_t *t)
{
	assert (t != NULL);
	_wp_bin_tree_flush (wp_tree_node_get_right (t->sent), t->sent);
	wp_tree_node_set_right (t->sent, t->sent);
	t->card = 0;
}

bool wp_rb_tree_is_empty (const wp_rb_tree_t *t)
{
	assert (t != NULL);
	return (t->card == 0);
}

int wp_rb_tree_get_card (const wp_rb_tree_t *t)
{
	assert (t != NULL);
	return (t->card);
}

int wp_rb_tree_get_height (const wp_rb_tree_t *t)
{
	assert (t != NULL);
	return _wp_bin_tree_height (wp_tree_node_get_right (t->sent), t->sent);
}

void *wp_rb_tree_get_root (const wp_rb_tree_t *t)
{
	assert (t != NULL);
	return wp_tree_node_get_content (wp_tree_node_get_right (t->sent));
}

void *wp_rb_tree_get_minimum (const wp_rb_tree_t *t)
{
	assert (t != NULL);
	return _wp_bin_tree_minimum (wp_tree_node_get_right (t->sent), t->sent);
}

void *wp_rb_tree_get_maximum (const wp_rb_tree_t *t)
{
	assert (t != NULL);
	return _wp_bin_tree_maximum (wp_tree_node_get_right (t->sent), t->sent);
}

void wp_rb_tree_insert (wp_rb_tree_t *t, void *data)
{
	wp_tree_node_t *x;
	wp_tree_node_t *y;
	wp_tree_node_t *z;
	
	assert (t != NULL);

	x = wp_tree_node_get_right (t->sent);
	y = t->sent;

	z = wp_tree_node_new_full (data, NULL, y, y);
	if (z == NULL)
	{
		return;
	}

	while (x != t->sent)
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

	wp_tree_node_set_parent (z, y);

	if (y == t->sent)	/* root */
	{
		wp_tree_node_set_right (t->sent, z);
	}
	else
	{
		if (t->cmp_f (data, wp_tree_node_get_content (y)) < 0)
		{
			wp_tree_node_set_left (y, z);
		}
		else
		{
			wp_tree_node_set_right (y, z);
		}
	}

	wp_tree_node_set_red (z);

	rb_insert_fixup (t, z);

	(t->card)++;
}

void *wp_rb_tree_search (const wp_rb_tree_t *t, void *data)
{
	wp_tree_node_t *tmp;

	assert (t != NULL);

	tmp = _wp_bin_tree_search (wp_tree_node_get_right (t->sent), t->sent, t->cmp_f, data);
	
	return (tmp == NULL) ? NULL : wp_tree_node_get_content (tmp);
}

void *wp_rb_tree_delete (wp_rb_tree_t *t, void *data)
{
	wp_tree_node_t *x;	/* y's not SENTINEL child, or SENTINEL if y don't have child */
	wp_tree_node_t *y;	/* the node actually delete */
	wp_tree_node_t *z;	/* the node contain data */
	wp_tree_node_t *py;	/* parent of y */

	assert (t != NULL);

	z = _wp_bin_tree_search (wp_tree_node_get_right (t->sent), t->sent, t->cmp_f, data);
	if (z == NULL)
	{
		fprintf (stderr, "warning!, return an NULL\n");
		return NULL;
	}

	if ((wp_tree_node_get_left (z) == t->sent) || (wp_tree_node_get_right (z) == t->sent))
	{
		y = z;
	}
	else
	{
		y = _wp_bin_tree_successor (z, t->sent);
	}

	if (wp_tree_node_get_left (y) != t->sent)
	{
		x = wp_tree_node_get_left (y);
	}
	else
	{
		x = wp_tree_node_get_right (y);
	}

	py = wp_tree_node_get_parent (y);
	wp_tree_node_set_parent (x, py);

	if (py == t->sent)
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

	if (wp_tree_node_is_black (y))
	{
		rb_delete_fixup (t, x);
	}

	wp_tree_node_free (y);
	(t->card)--;

	return data;
}

void wp_rb_tree_map_prefix (const wp_rb_tree_t *t, FILE *file, wp_write_func_t f, void *data)
{
	assert (t != NULL);
	assert (file != NULL);
	assert (f != NULL);
	_wp_bin_tree_map_prefix (wp_tree_node_get_right (t->sent), t->sent, file, f, data);
}
	
void wp_rb_tree_map_infix (const wp_rb_tree_t *t, FILE *file, wp_write_func_t f, void *data)
{
	assert (t != NULL);
	assert (file != NULL);
	assert (f != NULL);
	_wp_bin_tree_map_infix (wp_tree_node_get_right (t->sent), t->sent, file, f, data);
}

void wp_rb_tree_map_postfix (const wp_rb_tree_t *t, FILE *file, wp_write_func_t f, void *data)
{
	assert (t != NULL);
	assert (file != NULL);
	assert (f != NULL);
	_wp_bin_tree_map_postfix (wp_tree_node_get_right (t->sent), t->sent, file, f, data);
}

void wp_rb_tree_dump (const wp_rb_tree_t *t, FILE *file, wp_write_func_t f, void *data)
{
	assert (t != NULL);
	assert (file != NULL);
	fprintf (file, "<RB_TREE REF=\"%p\" CARD=\"%d\" SENT=\"%p\">\n", (void *)t, t->card, (void *)(t->sent));

	_wp_bin_tree_dump (wp_tree_node_get_right (t->sent), t->sent, file, f, data, RB_TREE);

	fprintf (file, "</RB_TREE>\n");	
}

void wp_rb_tree_foreach (wp_rb_tree_t *t, wp_foreach_func_t f, void *data)
{
	assert (t != NULL);
	assert (f != NULL);
	_wp_bin_tree_foreach (wp_tree_node_get_right (t->sent), t->sent, f, data);
}

/* private func */
static void left_rotate (wp_rb_tree_t *t, wp_tree_node_t *x)
{
	wp_tree_node_t *y;
	wp_tree_node_t *ly;
	wp_tree_node_t *px;

	assert (t != NULL);
	assert (x != NULL);

	/* Set y */
	y = wp_tree_node_get_right (x);
	assert (y != NULL);

	/* Turn y's left subtree into x's right subtree */
	ly = wp_tree_node_get_left (y);
	wp_tree_node_set_right (x, ly);
	if (ly != t->sent)
	{
		wp_tree_node_set_parent (ly, x);
	}
	
	/* Link x's parent to y */
	px = wp_tree_node_get_parent (x);
	wp_tree_node_set_parent (y, px);
	if (px == t->sent)	/* root */
	{
		wp_tree_node_set_right (t->sent, y);
	}
	else
	{
		if (x == wp_tree_node_get_left (px))
		{
			wp_tree_node_set_left (px, y);
		}
		else /* x == wp_tree_node_get_right (px) */
		{
			wp_tree_node_set_right (px, y);
		}
	}

	/* Put x on y's left*/
	wp_tree_node_set_left (y, x);
	wp_tree_node_set_parent (x, y);
}

static void right_rotate (wp_rb_tree_t *t, wp_tree_node_t *x)
{
	wp_tree_node_t *y;
	wp_tree_node_t *ry;
	wp_tree_node_t *px;

	assert (t != NULL);
	assert (x != NULL);

	/* Set y */
	y = wp_tree_node_get_left (x);
	assert (y != NULL);

	/* Turn y's right subtree into x's left subtree */
	ry = wp_tree_node_get_right (y);
	wp_tree_node_set_left (x, ry);
	if (ry != t->sent)
	{
		wp_tree_node_set_parent (ry, x);
	}

	/* Link x's parent to y */
	px = wp_tree_node_get_parent (x);
	wp_tree_node_set_parent (y, px);
	if (px == t->sent)
	{
		wp_tree_node_set_right (t->sent, y);
	}
	else
	{
		if (x == wp_tree_node_get_left (px))
		{
			wp_tree_node_set_left (px, y);
		}
		else /* x == wp_tree_node_get_right (px) */
		{
			wp_tree_node_set_right (px, y);
		}
	}
	
	/* Put x on y's right */
	wp_tree_node_set_right (y, x);
	wp_tree_node_set_parent (x, y);
}

static void rb_insert_fixup (wp_rb_tree_t *t, wp_tree_node_t *z)
{
	wp_tree_node_t *y;	/* z's uncle */
	wp_tree_node_t *pz;	/* z's parent */
	wp_tree_node_t *ppz;	/* z's parent's parent */

	static int i = 0;
	i++;

	while (wp_tree_node_is_red (wp_tree_node_get_parent (z))) /* so that p[p[z]] is black */
	{
		pz = wp_tree_node_get_parent (z);
		ppz = wp_tree_node_get_parent (pz);
		if (pz == wp_tree_node_get_left (ppz))
		{
			y = wp_tree_node_get_right (ppz);

			if (wp_tree_node_is_red (y))
			{
				wp_tree_node_set_black (pz);
				wp_tree_node_set_black (y);
				wp_tree_node_set_red (ppz);
				z = ppz;
			}
			else /* wp_tree_node_is_black (y) */
			{
				if (z == wp_tree_node_get_right (pz))
				{
					z = pz;
					left_rotate (t, z);
				}
				/* take care, z may has been changed */
				pz = wp_tree_node_get_parent (z);
				ppz = wp_tree_node_get_parent (pz);
	
				wp_tree_node_set_black (pz);
				wp_tree_node_set_red (ppz);
				right_rotate (t, ppz);
			}

		}
		else /* pz == wp_tree_node_get_right (ppz) */
		{
			y = wp_tree_node_get_left (ppz);

			if (wp_tree_node_is_red (y))
			{
				wp_tree_node_set_black (pz);
				wp_tree_node_set_black (y);
				wp_tree_node_set_red (ppz);
				z = ppz;
			}
			else /* wp_tree_node_is_black (y) */
			{
				if (z == wp_tree_node_get_left (pz))
				{
					z = pz;
					right_rotate (t, z);

					pz = wp_tree_node_get_parent (z);
					ppz = wp_tree_node_get_parent (pz);
				}
				
				wp_tree_node_set_black (pz);
				wp_tree_node_set_red (ppz);
				left_rotate (t, ppz);
			}
		}
	}

	wp_tree_node_set_black (wp_tree_node_get_right (t->sent));
}

static void rb_delete_fixup (wp_rb_tree_t *t, wp_tree_node_t *x)
{
	wp_tree_node_t *px;	/* x's parent */
	wp_tree_node_t *w;	/* x's brother */
	wp_tree_node_t *lw;
	wp_tree_node_t *rw;
	wp_tree_node_t *root;

	root = wp_tree_node_get_right (t->sent);
	while ((x != root) && wp_tree_node_is_black (x))
	{
		/* x is DOUBLE-BLACK now */
		px = wp_tree_node_get_parent (x);
		if (x == wp_tree_node_get_left (px))
		{
			w = wp_tree_node_get_right (px);
			if (wp_tree_node_is_red (w))
			{
				wp_tree_node_set_black (w);
				wp_tree_node_set_red (px);
				left_rotate (t, px);
				w = wp_tree_node_get_right (px);
			}

			lw = wp_tree_node_get_left (w);
			rw = wp_tree_node_get_right (w);
			if (wp_tree_node_is_black (lw) && wp_tree_node_is_black (rw)) /* both child are black, so w can be red */
			{
				wp_tree_node_set_red (w);
				x = px;
			}
			else /* one child or none are black, at least one is red */
			{
				if (wp_tree_node_is_black (rw))	/* so that lw is red */
				{
					wp_tree_node_set_black (lw);
					wp_tree_node_set_red (w);
					right_rotate (t, w);
					w = wp_tree_node_get_right (px);
					lw = wp_tree_node_get_left (w);
					rw = wp_tree_node_get_right (rw);
				}

				/* now rw is red */
				wp_tree_node_is_red (px) ? wp_tree_node_set_red (w) : wp_tree_node_set_black (w);
				wp_tree_node_set_black (px);
				wp_tree_node_set_black (rw);
				left_rotate (t, px);
				x = root;
			}
		}
		else /* x == wp_tree_node_get_right (px) */
		{
			w = wp_tree_node_get_left (px);
			if (wp_tree_node_is_red (w))
			{
				wp_tree_node_set_black (w);
				wp_tree_node_set_red (px);
				right_rotate (t, px);
				w = wp_tree_node_get_left (px);
			}

			lw = wp_tree_node_get_left (w);
			rw = wp_tree_node_get_right (w);
			if (wp_tree_node_is_black (lw) && wp_tree_node_is_black (rw))
			{
				wp_tree_node_set_red (w);
				x = px;
			}
			else /* one child or none are black, at least one is red */
			{
				if (wp_tree_node_is_black (lw))
				{
					wp_tree_node_set_black (rw);
					wp_tree_node_set_red (w);
					left_rotate (t, w);
					w = wp_tree_node_get_left (px);
					lw = wp_tree_node_get_left (w);
					rw = wp_tree_node_get_right (w);
				}

				/* now lw is red */
				wp_tree_node_is_red (px) ? wp_tree_node_set_red (w) : wp_tree_node_set_black (w);
				wp_tree_node_set_black (px);
				wp_tree_node_set_black (lw);
				right_rotate (t, px);
				x = root;
			}
		}
	}
	wp_tree_node_set_black (x);
}
