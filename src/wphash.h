#include <string.h>
#include <stdbool.h>

#ifndef __WPHASH_H__
#define __WPHASH_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef unsigned int (*WpHashFunc) (const void *key);
typedef void (*WpHFunc) (void *key, void *value, void *user_data);
typedef bool (*WpEqualFunc) (const void *a, const void *b);
typedef void (*WpDestroyNotify) (void *data);

typedef struct _WpHashTable WpHashTable;

typedef bool (*WpHRFunc) (void *key, void *value, void *user_data);

typedef struct _WpHashTableIter
{
	void 	*dummy1;
	void 	*dummy2;
	void	*dummy3;
	int		dummy4;
	void	*dummy5;
	void	*dummy6;
} WpHashTableIter;

WpHashTable *wp_hash_table_new (WpHashFunc hash_func,WpEqualFunc key_equal_func);
WpHashTable *wp_hash_table_new_full (WpHashFunc hash_func, WpEqualFunc key_equal_func, WpDestroyNotify key_destory_func, WpDestroyNotify value_destroy_func);
void wp_hash_table_destroy (WpHashTable *hash_table);
void wp_hash_table_insert (WpHashTable *hash_table, void *key, void *value);
void wp_hash_table_replace (WpHashTable *hash_table, void *key, void *value);
bool wp_hash_table_remove (WpHashTable *hash_table, const void *key);
void wp_hash_table_remove_all (WpHashTable *hash_table);
bool wp_hash_table_steal (WpHashTable *hash_table, const void *key);
void wp_hash_table_steal_all (WpHashTable *hash_table);
void *wp_hash_table_lookup (WpHashTable *hash_table, const void *key);
bool wp_hash_table_lookup_extended (WpHashTable *hash_table, const void *lookup_key, void **orig_key, void **value);
void wp_hash_table_foreach (WpHashTable *hash_table, WpHFunc func, void *user_data);
void *wp_hash_table_find (WpHashTable *hash_table, WpHRFunc predicate, void *user_data);
unsigned int wp_hash_table_foreach_remove (WpHashTable *hash_table, WpHRFunc func, void *user_data);
unsigned int wp_hash_table_foreach_steal (WpHashTable *hash_table, WpHRFunc func, void *user_data);
unsigned int wp_hash_table_size (WpHashTable *hash_table);
void wp_hash_table_iter_init (WpHashTableIter *iter, WpHashTable *hash_table);
bool wp_hash_table_iter_next (WpHashTableIter *iter, void *key, void *value);
WpHashTable *wp_hash_table_iter_get_hash_table (WpHashTableIter *iter);
void wp_hash_table_iter_remove (WpHashTableIter *iter);
void wp_hash_table_iter_steal (WpHashTableIter *iter);
WpHashTable *wp_hash_table_ref (WpHashTable *hash_table);
void wp_hash_table_unref (WpHashTable *hash_table);

bool wp_str_equal (const void *v1, const void *v2);
unsigned wp_str_hash (const void *v);
bool wp_int_equal (const void *v1, const void *v2);
unsigned int wp_int_hash (const void *v);
bool wp_int64_equal (const void *v1, const void *v2);
unsigned int wp_int64_hash (const void *v);
bool wp_double_equal (const void *v1, const void *v2);
unsigned int wp_double_hash (const void *v);
bool wp_direct_equal (const void *v1, const void *v2);
unsigned int wp_direct_hash (const void *v);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WPHASH_H__ */
