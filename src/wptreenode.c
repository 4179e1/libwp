#include <stdlib.h>
#include <assert.h>
#include "wptreenode.h"

#define RB_TREE_MASK 0x1

struct _wp_treenode
{
	void *content;
	/* take care this, we use the last bit of the pointer to idicate the node is red or black */
	unsigned long parent;
	wp_tree_node_t *left;
	wp_tree_node_t *right;
} __attribute__((aligned(sizeof(long))));

wp_tree_node_t *wp_tree_node_new (void)
{
	return (wp_tree_node_t *)calloc (1, sizeof (wp_tree_node_t));
}

wp_tree_node_t *wp_tree_node_new_full (void *content, wp_tree_node_t *parent, wp_tree_node_t *left, wp_tree_node_t *right)
{
	wp_tree_node_t *node;

	node = (wp_tree_node_t *)malloc (sizeof (wp_tree_node_t));
	node->content = content;
	node->parent = (unsigned long)parent;
	node->left = left;
	node->right = right;

	return node;
}

void wp_tree_node_copy (wp_tree_node_t *dest, const wp_tree_node_t *src)
{
	assert (dest != NULL);
	assert (src != NULL);

	dest->content = src->content;
	dest->parent = src->parent;
	dest->left = src->left;
	dest->right = src->right;
}

void wp_tree_node_free (wp_tree_node_t *node)
{
	assert (node != NULL);
	free (node);
}

void wp_tree_node_set_content (wp_tree_node_t *node, void *data)
{
	assert (node != NULL);
	node->content = data;
}

void wp_tree_node_set_parent (wp_tree_node_t *node, wp_tree_node_t *parent)
{
	int rb_status;
	assert (node != NULL);
	rb_status = ((node->parent) & RB_TREE_MASK);
	node->parent = (unsigned long) ((unsigned long)(parent) | rb_status);
}

void wp_tree_node_set_left (wp_tree_node_t *node, wp_tree_node_t *left)
{
	assert (node != NULL);
	node->left = left;
}

void wp_tree_node_set_right (wp_tree_node_t *node, wp_tree_node_t *right)
{
	assert (node != NULL);
	node->right = right;
}

void *wp_tree_node_get_content (const wp_tree_node_t *node)
{
	assert (node != NULL);
	return node->content;
}

wp_tree_node_t *wp_tree_node_get_parent (const wp_tree_node_t *node)
{
	assert (node != NULL);
	return (wp_tree_node_t *)((node->parent) & (~RB_TREE_MASK));
}

wp_tree_node_t *wp_tree_node_get_left (const wp_tree_node_t *node)
{
	assert (node != NULL);
	return node->left;
}

wp_tree_node_t *wp_tree_node_get_right (const wp_tree_node_t *node)
{
	assert (node != NULL);
	return node->right;
}

bool wp_tree_node_is_leaf (const wp_tree_node_t *node)
{
	assert (node != NULL);
	return ((node->left == NULL) && (node->right == NULL));
}

bool wp_tree_node_is_root (const wp_tree_node_t *node)
{
	assert (node != NULL);
	return (wp_tree_node_get_parent (node) == NULL);
}

/* For Red-Black Tree */
void wp_tree_node_set_red (wp_tree_node_t *node)
{
	assert (node != NULL);
	node->parent &= (~RB_TREE_BLACK);
}

void wp_tree_node_set_black (wp_tree_node_t *node)
{
	assert (node != NULL);
	node->parent |= RB_TREE_BLACK;
}

bool wp_tree_node_is_red (const wp_tree_node_t *node)
{
	assert (node != NULL);
	return (((node->parent) & RB_TREE_MASK ) == RB_TREE_RED);
}

bool wp_tree_node_is_black (const wp_tree_node_t *node)
{
	assert (node != NULL);
	return (((node->parent) & RB_TREE_MASK ) == RB_TREE_BLACK);
}

Rbwp_tree_node_tColor wp_tree_node_get_color (const wp_tree_node_t *node)
{
	assert (node != NULL);

	return (node->parent & RB_TREE_MASK);
}

void wp_tree_node_set_color (wp_tree_node_t *node, Rbwp_tree_node_tColor color)
{
	assert (node != NULL);
	if (color == RB_TREE_RED)
	{
		node->parent &= (~RB_TREE_BLACK);
	}
	else /* color = RB_TREE_BLACK */
	{
		node->parent |= RB_TREE_BLACK;
	}
}

void wp_tree_node_copy_color (wp_tree_node_t *dest, const wp_tree_node_t *src)
{
	wp_tree_node_set_color (dest, wp_tree_node_get_color (src));
}

void wp_tree_node_dump (const wp_tree_node_t *node, FILE *file, wp_write_func_t f, void *data)
{
	fprintf (file, "<TREE_NODE REF=\"%p\" CONTENT=\"%p\" PARENT=\"%p\" LEFT=\"%p\" RIGHT=\"%p\">", (void *)node, (void *)node->content, (void *)wp_tree_node_get_parent (node), (void *)node->left, (void *)node->right);
	if (f)
	{
		f (node->content, file, data);
	}
	fprintf (file, "</TREE_NODE>\n");
}

void rb_wp_tree_node_dump (const wp_tree_node_t *node, FILE *file, wp_write_func_t f, void *data)
{
	fprintf (file, "<TREE_NODE TYPE=\"%s\" REF=\"%p\" CONTENT=\"%p\" PARENT=\"%p\" LEFT=\"%p\" RIGHT=\"%p\">",
			(wp_tree_node_is_black (node) ? "BLACK" : "RED"), (void *)node, (void *)node->content, (void *)wp_tree_node_get_parent (node), (void *)node->left, (void *)node->right);
	if (f)
	{
		f (node->content, file, data);
	}
	fprintf (file, "</TREE_NODE>\n");
}

