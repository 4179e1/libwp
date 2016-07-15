#include <wpmacros.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wphash.h>
#include <wpmacros.h>

#define HASH_TABLE_MIN_SHIFT 3 /* 1 << 3 == 8 buckets */

typedef struct _wp_hash_node wp_hash_node_t;
struct _wp_hash_node
{
	void *key;
	void *value;
	/* If key_hash == 0, node is not in use
	 * If key_hash == 1, node is a tombstone
	 * If key_hash >= 2, node cotains data */
	unsigned int key_hash;
};

struct _wp_hash_table
{
	int 			size;		/* size of ht */
	int				mod;		/* mod int that size, see prime_mod[] */
	unsigned int	nnodes;
	unsigned int	mask;
	int				noccupied; /* nnodes + tombstones */
	wp_hash_node_t		*nodes;
	wp_hash_func_t		hash_func;
	wp_equal_func_t		key_equal_func;
	volatile int	ref_count;
	int				version;
	WpDestroyNotify key_destroy_func;
	WpDestroyNotify value_destroy_func;
};

typedef struct
{
	wp_hash_table_t	*hash_table;
	void		*dummy1;
	void		*dummy2;
	int			position;
	bool		dummy3;
	int			version;
}RealIter;

static const int prime_mod[] = 
{
	1,          /* For 1 << 0 */
	2,
	3,
	7,
	13,
	31,
	61,
	127,
	251,
	509,
	1021,
	2039,
	4093,
	8191,
	16381,
	32749,
	65521,      /* For 1 << 16 */
	131071,
	262139,
	524287,
	1048573,
	2097143,
	4194301,
	8388593,
	16777213,
	33554393,
	67108859,
	134217689,
	268435399,
	536870909,
	1073741789,
	2147483647  /* For 1 << 31 */
};

static void wp_hash_table_set_shift (wp_hash_table_t *hash_table, int shift)
{
	int i;
	unsigned int mask = 0;

	hash_table->size = 1 << shift;
	hash_table->mod = prime_mod[shift];

	for (i = 0; i < shift; i++)
	{
		mask <<=1;
		mask |= 1;
	}
	
	hash_table->mask = mask;
}

static int
wp_hash_table_find_closest_shift (int n)
{
	int i;

	for (i = 0; n; i++)
	{
		n>>=1;
	}

	return i;
}

static void
wp_hash_table_set_shift_from_size (wp_hash_table_t *hash_table, int size)
{
	int shift;

	shift = wp_hash_table_find_closest_shift (size);
	shift = (shift > HASH_TABLE_MIN_SHIFT ? shift : HASH_TABLE_MIN_SHIFT);

	wp_hash_table_set_shift (hash_table, shift);
}

static void
wp_hash_table_remove_all_nodes (wp_hash_table_t *hash_table, bool notify)
{
	int i;
	for (i = 0; i < hash_table->size; i++)
	{
		wp_hash_node_t *node = &hash_table->nodes[i];

		if (node->key_hash > 1)
		{
			if (notify && hash_table->key_destroy_func)
			{
				hash_table->key_destroy_func (node->key);
			}
			if (notify && hash_table->value_destroy_func)
			{
				hash_table->value_destroy_func (node->value);
			}
		}

	}

	memset (hash_table->nodes, 0, hash_table->size * sizeof (wp_hash_table_t));

	hash_table->nodes = 0;
	hash_table->noccupied = 0;
}

static void
wp_hash_table_resize (wp_hash_table_t *hash_table)
{
	wp_hash_node_t *new_nodes;
	int old_size;
	int i;

	old_size = hash_table->size;
	wp_hash_table_set_shift_from_size (hash_table, hash_table->nnodes * 2);

	new_nodes = calloc (hash_table->size, sizeof (wp_hash_node_t));
	wp_return_if_fail (new_nodes != NULL);

	for (i = 0; i < old_size; i++)
	{
		wp_hash_node_t *node = &hash_table->nodes[i];
		wp_hash_node_t *new_node;
		unsigned int hash_val;
		unsigned int step = 0;

		if (node->key_hash <= 1)
		{
			continue;
		}

		hash_val = node->key_hash % hash_table->mod;
		new_node = &new_nodes[hash_val];

		while (new_node->key_hash)
		{
			step++;
			hash_val += step;
			hash_val &= hash_table->mask; /* to make sure stack don't overflow */
			new_node = &new_nodes[hash_val];
		}

		*new_node = *node;
	}

	free (hash_table->nodes);
	hash_table->nodes = new_nodes;
	hash_table->noccupied = hash_table->nnodes;
}

static inline void
wp_hash_table_maybe_resize (wp_hash_table_t *hash_table)
{
	int noccupied = hash_table->noccupied;
	int size = hash_table->size;

	if ((size > hash_table->nnodes * 4 && size > 1 << HASH_TABLE_MIN_SHIFT) || (size <= noccupied + (noccupied / 16)))
	{
		wp_hash_table_resize  (hash_table);
	}
}

static inline unsigned
wp_hash_table_lookup_node (wp_hash_table_t *hash_table, const void *key)
{
	wp_hash_node_t *node;
	unsigned int node_index;
	unsigned int hash_value;
	unsigned step = 0;

	hash_value = (* hash_table->hash_func)(key);
	if (hash_value <= 1)
	{
		hash_value = 2;
	}

	node_index = hash_value % hash_table->mod;
	node = &hash_table->nodes[node_index];
	while (node->key_hash)
	{
		if (node->key_hash == hash_value)
		{
			if (hash_table->key_equal_func)
			{
				if (hash_table->key_equal_func (node->key, key))
				{
					break;
				}
			}
			else if (node->key == key) /* direct equal, just compare address */
			{
				break;
			}
		}

		step++;
		node_index += step;
		node_index &= hash_table->mask;
		node = &hash_table->nodes[node_index];
	}

	return node_index;
}

wp_hash_table_t *
wp_hash_table_new (wp_hash_func_t hash_func, wp_equal_func_t key_equal_func)
{
	return wp_hash_table_new_full (hash_func, key_equal_func, NULL, NULL);
}

wp_hash_table_t *
wp_hash_table_new_full (wp_hash_func_t hash_func, wp_equal_func_t key_equal_func, WpDestroyNotify key_destroy_func, WpDestroyNotify value_destroy_func)
{
	wp_hash_table_t *hash_table;

	hash_table = malloc (sizeof (wp_hash_table_t));
	if (hash_table == NULL)
	{
		return NULL;
	}
	wp_hash_table_set_shift (hash_table, HASH_TABLE_MIN_SHIFT);
	hash_table->nnodes 				= 0;
	hash_table->noccupied			= 0;
	hash_table->hash_func			= hash_func ? hash_func : wp_direct_hash;
	hash_table->key_equal_func		= key_equal_func;
	hash_table->ref_count			= 1;
	hash_table->key_destroy_func	= key_destroy_func;
	hash_table->value_destroy_func	= value_destroy_func;
	hash_table->nodes 				= calloc (hash_table->size, sizeof (wp_hash_table_t));
	if (hash_table->nodes == NULL)
	{
		free (hash_table);
		return NULL;
	}

	return hash_table;
}

wp_hash_table_t *wp_hash_table_ref (wp_hash_table_t *hash_table)
{
	wp_return_val_if_fail (hash_table != NULL, NULL);
	wp_return_val_if_fail (hash_table->ref_count > 0, hash_table);

	__sync_fetch_and_add (&hash_table->ref_count, 1);

	return hash_table;
}

void wp_hash_table_unref (wp_hash_table_t *hash_table)
{
	wp_return_if_fail (hash_table != NULL);
	wp_return_if_fail (hash_table->ref_count > 0);

	if (__sync_fetch_and_add (&hash_table->ref_count, -1) - 1 == 0)
	{
		wp_hash_table_remove_all_nodes (hash_table, true);
		free (hash_table->nodes);
		free (hash_table);
	}
}

void wp_hash_table_destroy (wp_hash_table_t *hash_table)
{
	wp_return_if_fail (hash_table != NULL);
	wp_return_if_fail (hash_table->ref_count > 0);

	wp_hash_table_remove_all (hash_table);
	wp_hash_table_unref (hash_table);
}

void *wp_hash_table_lookup (wp_hash_table_t *hash_table, const void *key)
{
	wp_hash_node_t *node;
	unsigned int node_index;

	wp_return_val_if_fail (hash_table != NULL, NULL);

	node_index = wp_hash_table_lookup_node (hash_table, key);
	node = &hash_table->nodes[node_index];

	return node->key_hash ? node->value : NULL;
}

bool wp_hash_table_lookup_extended (wp_hash_table_t *hash_table, const void *lookup_key, void **orig_key, void **value)
{
	wp_hash_node_t *node;
	unsigned int node_index;

	wp_return_val_if_fail (hash_table != NULL, NULL);

	node_index = wp_hash_table_lookup_node (hash_table, lookup_key);
	node = &hash_table->nodes[node_index];

	if (!node->key_hash)
	{
		return false;
	}

	if (orig_key)
	{
		*orig_key = node->key;
	}

	if (value)
	{
		*value = node->value;
	}

	return true;
}

void wp_hash_table_remove_all (wp_hash_table_t *hash_table)
{
	wp_return_if_fail (hash_table != NULL);

	wp_hash_table_remove_all_nodes (hash_table, true);
	wp_hash_table_maybe_resize (hash_table);
}

static inline unsigned int
wp_hash_table_lookup_node_for_insertion (wp_hash_table_t *hash_table, const void *key, unsigned int *hash_return)
{
	wp_hash_node_t *node;
	unsigned int node_index;
	unsigned int hash_value;
	unsigned int first_tombstone = 0;
	bool have_tombstone = false;
	unsigned int step = 0;

	hash_value = (*hash_table->hash_func)(key);
	if (hash_value <= 1)
	{
		hash_value = 2;
	}

	*hash_return = hash_value;

	node_index = hash_value % hash_table->mod;
	node = &hash_table->nodes[node_index];

	while (node->key_hash)
	{
		if (hash_table->key_equal_func)
		{
			if (hash_table->key_equal_func (node->key, key))
			{
				return node_index;
			}
			else if (node->key == key)
			{
				return node_index;
			}
		}
		else if (node->key_hash == 1 && !have_tombstone)
		{
			first_tombstone = node_index;
			have_tombstone = true;
		}

		step++;
		node_index += step;
		node_index &= hash_table->mask;
		node = &hash_table->nodes[node_index];
	}

	if (have_tombstone)
	{
		return first_tombstone;
	}

	return node_index;
}

static void 
wp_hash_table_insert_internal (wp_hash_table_t *hash_table, void *key, void *value, bool keep_new_key)
{
	wp_hash_node_t *node;
	unsigned int node_index;
	unsigned int key_hash;
	unsigned int old_hash;

	wp_return_if_fail (hash_table != NULL);
	wp_return_if_fail (hash_table->ref_count > 0);
	
	node_index = wp_hash_table_lookup_node_for_insertion (hash_table, key, &key_hash);
	node = &hash_table->nodes[node_index];

	old_hash = node->key_hash;

	if (old_hash > 1)
	{
		if (keep_new_key)
		{
			if (hash_table->key_destroy_func)
			{
				hash_table->key_destroy_func (node->key);
			}
			node->key = key;
		}
		else
		{
			if (hash_table->key_destroy_func)
			{
				hash_table->key_destroy_func (key);
			}
		}

		if (hash_table->value_destroy_func)
		{
			hash_table->value_destroy_func (node->value);
		}
		node->value = value;
	}
	else
	{
		node->key = key;
		node->value = value;
		node->key_hash = key_hash;

		hash_table->nnodes++;

		if (old_hash == 0)
		{
			hash_table->noccupied++;
			wp_hash_table_maybe_resize (hash_table);
		}
	}
}

void wp_hash_table_insert (wp_hash_table_t *hash_table, void *key, void *value)
{
	wp_hash_table_insert_internal (hash_table, key, value, false);
}

void wp_hash_table_replace (wp_hash_table_t *hash_table, void *key, void *value)
{
	wp_hash_table_insert_internal (hash_table, key, value, true);
}

static void
wp_hash_table_remove_node (wp_hash_table_t *hash_table, wp_hash_node_t *node, bool notify)
{
	if (notify && hash_table->key_destroy_func)
	{
		hash_table->key_destroy_func (node->key);
	}

	if (notify && hash_table->value_destroy_func)
	{
		hash_table->value_destroy_func (node->value);
	}

	node->key_hash = 1;
	node->key = NULL;
	node->value = NULL;

	hash_table->nnodes--;
}

static bool 
wp_hash_table_remove_internal (wp_hash_table_t *hash_table, const void *key, bool notify)
{
	wp_hash_node_t *node;
	unsigned int node_index;

	wp_return_val_if_fail (hash_table != NULL, false);

	node_index = wp_hash_table_lookup_node (hash_table, key);
	node = &hash_table->nodes[node_index];

	if (!node->key_hash)
	{
		return false;
	}

	wp_hash_table_remove_node (hash_table, node, notify);
	wp_hash_table_maybe_resize (hash_table);

	return true;
}

bool wp_hash_table_remove (wp_hash_table_t *hash_table, const void *key)
{
	return wp_hash_table_remove_internal (hash_table, key, false);
}

bool wp_hash_table_steal (wp_hash_table_t *hash_table, const void *key)
{
	return wp_hash_table_remove_internal (hash_table, key, true);
}

void wp_hash_table_steal_all (wp_hash_table_t *hash_table)
{
	wp_return_if_fail (hash_table != NULL);

	wp_hash_table_remove_all_nodes (hash_table, false);
	wp_hash_table_maybe_resize (hash_table);
}

static unsigned int
wp_hash_table_foreach_remove_or_steal (wp_hash_table_t *hash_table, wp_hash_table_remove_foreach_func_t func, void *user_data, bool notify)
{
	unsigned deleted = 0;
	int i;

	for (i = 0; i < hash_table->size; i++)
	{
		wp_hash_node_t *node = &hash_table->nodes[i];

		if (node->key_hash > 1 && (*func) (node->key, node->value, user_data))
		{
			wp_hash_table_remove_node (hash_table, node, notify);
			deleted++;
		}
	}

	wp_hash_table_maybe_resize (hash_table);

	return deleted;
}

unsigned int wp_hash_table_foreach_remove (wp_hash_table_t *hash_table, wp_hash_table_remove_foreach_func_t func, void *user_data)
{
	wp_return_val_if_fail (hash_table != NULL, 0);
	wp_return_val_if_fail (func != NULL, 0);

	return wp_hash_table_foreach_remove_or_steal (hash_table, func, user_data, true);
}

unsigned int wp_hash_table_foreach_steal (wp_hash_table_t *hash_table, wp_hash_table_remove_foreach_func_t func, void *user_data)
{
	wp_return_val_if_fail (hash_table != NULL, 0);
	wp_return_val_if_fail (func != NULL, 0);

	return wp_hash_table_foreach_remove_or_steal (hash_table, func, user_data, true);
}

void wp_hash_table_foreach (wp_hash_table_t *hash_table, wp_hash_table_foreach_func_t func, void *user_data)
{
	int i;
	wp_return_if_fail (hash_table != NULL);
	wp_return_if_fail (func != NULL);

	for (i = 0; i < hash_table->size; i++)
	{
		wp_hash_node_t *node = &hash_table->nodes[i];

		if (node->key_hash > 1)
		{
			(* func)(node->key, node->value, user_data);
		}
	}
}

void *wp_hash_table_find (wp_hash_table_t *hash_table, wp_hash_table_remove_foreach_func_t predicate, void *user_data)
{
	int i;

	wp_return_val_if_fail (hash_table != NULL, NULL);
	wp_return_val_if_fail (predicate != NULL, NULL);

	for (i = 0; i < hash_table->size; i++)
	{
		wp_hash_node_t *node = &hash_table->nodes[i];

		if (node->key_hash > 1 && predicate (node->key, node->value, user_data))
		{
			return node->value;
		}

	}
	return NULL;
}

unsigned int wp_hash_table_size (wp_hash_table_t *hash_table)
{
	wp_return_val_if_fail (hash_table != NULL, 0);

	return hash_table->nnodes;
}

bool wp_str_equal (const void *v1, const void *v2)
{
	return (strcmp ((const char *)v1, (const char *)v2) == 0);
}

unsigned int wp_str_hash (const void *v)
{
	const signed char *p;
	unsigned int h = 5381;

	for (p = v; *p != '\0'; p++)
	{
		/* h = h * 33 + c */
		h = (h << 5) + h + *p;
	}

	return h;
}

bool wp_direct_equal (const void *v1, const void *v2)
{
	return (v1 == v2);
}

unsigned int wp_direct_hash (const void *v)
{
	return (unsigned int)v;
}
