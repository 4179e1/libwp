/**
 * Yesterday i had a job interview, the examier asked me to write a wp_queue
 * with enqueue & dequeue operation. Ater serval minutes, I said I can't 
 * finish it in such a short time.
 *		"It's it very difficult?"
 *		"No."
 * I didn't say more. How would they think a queue wrote in 5 minutes have
 * any usability? It may explosive at any second. I could worte a complete
 * and safe wp_queue in 2 hour, but not one uncomplete & unsafe in 5 minutes.
 */

#ifndef _QUEUE_H
#define _QUEUE_H
#include <stdbool.h>
#include "wpbase.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _wp_queue wp_queue_t;

wp_queue_t *wp_queue_new(int size);
void wp_queue_free (wp_queue_t *q);
void wp_queue_flush (wp_queue_t *q);

bool wp_queue_is_empty (const wp_queue_t *q);
int wp_queue_get_size (const wp_queue_t *q);
int wp_queue_get_card (const wp_queue_t *q);
int wp_queue_get_growing_factor (const wp_queue_t *q);
void wp_queue_set_growing_factor (wp_queue_t *q, int value);

void wp_queue_push_head (wp_queue_t *q, void *data);
void wp_queue_push_tail (wp_queue_t *q, void *data);
void *wp_queue_head (const wp_queue_t *q);
void *wp_queue_tail (const wp_queue_t *q);
void *wp_queue_pop_head (wp_queue_t *q);
void *wp_queue_pop_tail (wp_queue_t *q);

void wp_queue_dump (const wp_queue_t *q, FILE *file, wp_write_func_t f, void *data);
void wp_queue_foreach (const wp_queue_t *q, wp_foreach_func_t f, void *data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _QUEUE_H */
