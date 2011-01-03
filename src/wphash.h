#include <string.h>
#include <stdbool.h>

#ifndef _WPHASH_H
#define _WPHASH_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef unsigned int (*wp_hash_func_t) (const void *key);
typedef void (*wp_hash_table_foreach_func_t) (void *key, void *value, void *user_data);
typedef bool (*wp_equal_func_t) (const void *a, const void *b);
typedef void (*WpDestroyNotify) (void *data);

typedef struct _wp_hash_table wp_hash_table_t;

typedef bool (*wp_hash_table_remove_foreach_func_t) (void *key, void *value, void *user_data);

wp_hash_table_t *wp_hash_table_new (wp_hash_func_t hash_func,wp_equal_func_t key_equal_func);
wp_hash_table_t *wp_hash_table_new_full (wp_hash_func_t hash_func, wp_equal_func_t key_equal_func, WpDestroyNotify key_destory_func, WpDestroyNotify value_destroy_func);
void wp_hash_table_destroy (wp_hash_table_t *hash_table);
void wp_hash_table_insert (wp_hash_table_t *hash_table, void *key, void *value);
void wp_hash_table_replace (wp_hash_table_t *hash_table, void *key, void *value);
bool wp_hash_table_remove (wp_hash_table_t *hash_table, const void *key);
void wp_hash_table_remove_all (wp_hash_table_t *hash_table);
bool wp_hash_table_steal (wp_hash_table_t *hash_table, const void *key);
void wp_hash_table_steal_all (wp_hash_table_t *hash_table);
void *wp_hash_table_lookup (wp_hash_table_t *hash_table, const void *key);
bool wp_hash_table_lookup_extended (wp_hash_table_t *hash_table, const void *lookup_key, void **orig_key, void **value);
void wp_hash_table_foreach (wp_hash_table_t *hash_table, wp_hash_table_foreach_func_t func, void *user_data);
void *wp_hash_table_find (wp_hash_table_t *hash_table, wp_hash_table_remove_foreach_func_t predicate, void *user_data);
unsigned int wp_hash_table_foreach_remove (wp_hash_table_t *hash_table, wp_hash_table_remove_foreach_func_t func, void *user_data);
unsigned int wp_hash_table_foreach_steal (wp_hash_table_t *hash_table, wp_hash_table_remove_foreach_func_t func, void *user_data);
unsigned int wp_hash_table_size (wp_hash_table_t *hash_table);
wp_hash_table_t *wp_hash_table_ref (wp_hash_table_t *hash_table);
void wp_hash_table_unref (wp_hash_table_t *hash_table);

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

#endif /* _WPHASH_H */
