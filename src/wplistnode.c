#include <stdlib.h>
#include <assert.h>
#include <wplistnode.h>
#include <wpbase.h>

struct _wp_list_node
{
	void *data;
	struct _wp_list_node *prev;
	struct _wp_list_node *next;
};

wp_list_node_t *wp_list_node_new (void)
{
	wp_list_node_t *node;
	node = (wp_list_node_t *)malloc (sizeof (wp_list_node_t));
	if (node == NULL)
	{
		return NULL;
	}
	node->data = NULL;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

wp_list_node_t *wp_list_node_new_full (void *data, wp_list_node_t *p, wp_list_node_t *n)
{
	wp_list_node_t *node;
	node = (wp_list_node_t *)malloc (sizeof (wp_list_node_t));
	if (node == NULL)
	{
		return NULL;
	}
	node->data = data;
	node->prev = p;
	node->next = n;
	return node;
}

void wp_list_node_free (wp_list_node_t *n)
{
	free (n);
}

void wp_list_node_set_content (wp_list_node_t *node, void *data)
{
	assert (node != NULL);
	node->data = data;
}

void wp_list_node_set_next (wp_list_node_t *node, wp_list_node_t *next)
{
	assert (node != NULL);
	node->next = next;
}

void wp_list_node_set_prev (wp_list_node_t *node, wp_list_node_t *prev)
{
	assert (node != NULL);
	node->prev = prev;
}

void *wp_list_node_get_content (const wp_list_node_t *node)
{
	assert (node != NULL);
	return node->data;
}

wp_list_node_t *wp_list_node_get_next (const wp_list_node_t *node)
{
	assert (node != NULL);
	return node->next;
}

wp_list_node_t *wp_list_node_get_prev (const wp_list_node_t *node)
{
	assert (node != NULL);
	return node->prev;
}

void wp_list_node_link (wp_list_node_t *prev, wp_list_node_t *next)
{
	assert (prev != NULL);
	assert (next != NULL);
	prev->next = next;
	next->prev = prev;
}

void wp_list_node_unlink (wp_list_node_t *prev, wp_list_node_t *next)
{
	assert (prev != NULL);
	assert (prev != NULL);
	prev->next = NULL;
	next->prev = NULL;
}

void wp_list_node_insert_before (wp_list_node_t *n, wp_list_node_t *prev)
{
	wp_list_node_t *tmp;

	assert (n != NULL);
	assert (prev != NULL);

	tmp = n->prev;
	wp_list_node_link (prev, n);

	prev->prev = tmp;
	if (tmp)
	{
		tmp->next = prev;
	}
}

void wp_list_node_insert_after (wp_list_node_t *n, wp_list_node_t *next)
{
	wp_list_node_t *tmp;
	
	assert (n != NULL);
	assert (next != NULL);

	tmp = n->next;
	wp_list_node_link (n, next);

	next->next = tmp;
	if (tmp)
	{
		tmp->prev = next;
	}
}

void wp_list_node_dump (const wp_list_node_t *node, FILE *file, wp_write_func_t f, void *data)
{
	assert (node != NULL);
	assert (file != NULL);

	fprintf (file, "<LIST_NODE REF=\"%p\" CONTENT=\"%p\" PREV=\"%p\" NEXT=\"%p\">", (void *)node, (void *)node->data, (void *)node->prev, (void *)node->next);
	if (f)
	{
		f(node->data, file, data);
	}
	fprintf (file, "</LIST_NODE>\n");
}
