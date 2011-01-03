#ifndef _WPTYPES_H
#define _WPTYPES_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef bool (*wp_foreach_func_t) (void *elem, void *data);
typedef void (*wp_write_func_t) (const void *elem, FILE *file, void *data);
typedef int (*wp_compare_func_t) (const void *elem1, const void *elem2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPTYPES_H */

