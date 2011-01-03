#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <wpqueue.h>

/**
 *           q->head      q->tail 
 *              |            |
 * BEGIN -------+++++++++++++----------- END
 * 
 * + elements in wp_queue
 * - not used spaces in array
 */

static int prev (int cur, int size);
static int next (int cur, int size);

struct _wp_queue
{
	void **data;
	int head;
	int tail;
	int size;
	int card;
	int growing_factor;
};

wp_queue_t *wp_queue_new(int size)
{
	wp_queue_t *q;
	q = (wp_queue_t *)malloc (sizeof (wp_queue_t));
	if (q == NULL)
	{
		return NULL;
	}

	q->data = (void **)malloc (sizeof (void*) * size);
	if (q->data == NULL)
	{
		free (q);
		return NULL;
	}

	q->tail = 0;
	q->head = 0;
	q->size = size;
	q->card = 0;
	q->growing_factor = 10;

	return q;
}

void wp_queue_free (wp_queue_t *q)
{
	assert (q != NULL);
	free (q->data);
	free (q);
}

void wp_queue_flush (wp_queue_t *q)
{
	assert (q != NULL);
	q->head = 0;
	q->tail = 0;
	q->card = 0;
}

bool wp_queue_is_empty (const wp_queue_t *q)
{
	assert (q != NULL);
	return (q->card == 0);
}

int wp_queue_get_size (const wp_queue_t *q)
{
	assert (q != NULL);
	return q->size;
}

int wp_queue_get_card (const wp_queue_t *q)
{
	assert (q != NULL);
	return q->card;
}

int wp_queue_get_growing_factor (const wp_queue_t *q)
{
	assert (q != NULL);
	return q->growing_factor;
}

void wp_queue_set_growing_factor (wp_queue_t *q, int value)
{
	assert (q != NULL);
	q->growing_factor = value;
}

void wp_queue_push_head (wp_queue_t *q, void *data)
{
	assert (q != NULL);
	(q->card)++;
	if ((q->card) == (q->size))
	{
		int i, cur;
		void **tmp;
		(q->card)--;
		tmp = (void **)malloc (sizeof(void *) * ((q->size) + (q->growing_factor)));
		if (tmp == NULL)
		{
			return;
		}
		for (i = 0, cur = q->head; i < q->card; i++, cur = next (cur, q->size))
		{
			tmp[i] = q->data[cur];
		}
		free (q->data);
		q->data = tmp;
		q->head = 0;
		q->tail = q->card;
		q->size += q->growing_factor;
		(q->card)++;
	}
	q->head = prev (q->head, q->size);
	q->data[q->head] = data;
}

void wp_queue_push_tail (wp_queue_t *q, void *data)
{
	assert (q != NULL);
	(q->card++);
	if ((q->card) == (q->size))
	{
		int i, cur;
		void **tmp;
		(q->card)--;
		tmp = (void **)malloc (sizeof(void *) * ((q->size) + (q->growing_factor)));
		if (tmp == NULL)
		{
			return;
		}
		for (i = 0, cur = q->head; i < q->card; i++, cur = next (cur, q->size))
		{
			tmp[i] = q->data[cur];
		}
		free (q->data);
		q->data = tmp;
		q->head = 0;
		q->tail = q->card;
		q->size += q->growing_factor;
		(q->card)++;
	}
	q->data[q->tail] = data;
	q->tail = next (q->tail, q->size);
}

void *wp_queue_head (const wp_queue_t *q)
{
	assert (q != NULL);
	return q->data[q->head];
}

void *wp_queue_tail (const wp_queue_t *q)
{
	assert (q != NULL);
	return q->data[next (q->tail, q->size)];
}

void *wp_queue_pop_head (wp_queue_t *q)
{
	void *tmp;

	assert (q != NULL);
	tmp = q->data[q->head];
	q->head = next (q->head, q->size);
	(q->card)--;
	return tmp;
}

void *wp_queue_pop_tail (wp_queue_t *q)
{
	assert (q != NULL);
	q->tail = prev (q->tail, q->size);
	(q->card)--;
	return q->data[q->tail];
}

void wp_queue_dump (const wp_queue_t *q, FILE *file, wp_write_func_t f, void *data)
{
	int i, cur;
	assert (q != NULL);
	fprintf (file, "<QUEUE HEAD=\"%d\" TAIL=\"%d\" CARD=\"%d\" SIZE=\"%d\" GROWING_FACTOR=\"%d\">", q->head, q->tail, q->card, q->size, q->growing_factor);
	for (i = 0, cur = q->head; i < q->card; i++, cur = next (cur, q->size))
	{
		fprintf (file, "<NODE CONTENT=\"%p\" CUR=\"%d\">", q->data[cur], cur);
		if (f)
		{
			f(q->data[cur], file, data);
		}
		fprintf (file, "</NODE>");
	}
	fprintf (file, "</QUEUE>\n");
}

void wp_queue_foreach (const wp_queue_t *q, wp_foreach_func_t f, void *data)
{
	int i, cur;

	assert (q != NULL);
	for (i = 0, cur = q->head; i < q->card; i++, cur = next (cur, q->size))
	{
		if (f(q->data[cur], data) == false)
		{
			break;
		}
	}
}

/**
 * private func 
 */
static int next (int cur, int size)
{
	return ((cur + 1) % size);
}

static int prev (int cur, int size)
{
	return ((cur + size - 1) % size);
}
