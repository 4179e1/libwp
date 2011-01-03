#include <stdlib.h>
#include <wpmacros.h>
#include <wpstack.h>

struct _wp_stack
{
	void **data;
	int growing_factor;
	int size;
	int card;
};

wp_stack_t *stack_new (int size)
{
	wp_stack_t *s;
	wp_return_val_if_fail (size > 0, NULL);

	s = (wp_stack_t *)malloc (sizeof (wp_stack_t));
	if (s == NULL)
	{
		return NULL;
	}

	s->data = (void **)malloc (sizeof (void*) * size);
	if (s->data == NULL)
	{
		free (s);
		return NULL;
	}

	s->growing_factor = 10;
	s->size = size;
	s->card = 0;

	return s;
}

void stack_free (wp_stack_t *s)
{
	wp_return_if_fail (s != NULL);
	free (s->data);
	free (s);
}

void stack_flush (wp_stack_t *s)
{
	wp_return_if_fail (s != NULL);
	s->card = 0;
}

int stack_is_empty (const wp_stack_t *s)
{
	wp_return_val_if_fail (s != NULL, -1);
	return (s->card == 0);
}

int stack_get_size (const wp_stack_t *s)
{
	wp_return_val_if_fail (s != NULL, -1);
	return s->size;
}

int stack_get_card (const wp_stack_t *s)
{
	wp_return_val_if_fail (s != NULL, -1);
	return s->card;
}

int stack_get_growing_factor (const wp_stack_t *s)
{
	wp_return_val_if_fail (s != NULL, -1);
	return s->growing_factor;
}

void stack_set_growing_factor (wp_stack_t *s, int value)
{
	wp_return_if_fail (s != NULL);
	s->growing_factor = value;
}

void stack_push (wp_stack_t *s, void *data)
{
	wp_return_if_fail (s != NULL);

	(s->card++);
	if ((s->card) == (s->size))
	{
		s->data = realloc (s->data, (s->size) + (s->growing_factor));
		if (s->data == NULL)
		{
			return;
		}
		s->size += s->growing_factor;
	}
	s->data[s->card - 1] = (void *)data;
}

void *stack_pop (wp_stack_t *s)
{
	if (s->card == 0)
	{
		fprintf (stderr, "wp_stack_t is empty\n");
		return NULL;
	}
	(s->card)--;
	return s->data[s->card];
}

void *stack_top (const wp_stack_t *s)
{
	if (s->card == 0)
	{
		fprintf (stderr, "wp_stack_t is empty\n");
		return NULL;
	}
	return s->data[s->card - 1];
}

void stack_dump (const wp_stack_t *s, FILE *file, wp_write_func_t f, void *data)
{
	int i;
	fprintf (file, "<STACK SIZE=\"%d\" CARD=\"%d\" GROWING_FACTOR=\"%d\">", s->size, s->card, s->growing_factor);
	for (i = 0; i < (s->card); i++)
	{
		fprintf (file, "<NODE CONTENT=\"%p\">", s->data[i]);
		if (f)
		{
			f(s->data[i], file, data);
		}
		fprintf (file, "</NODE>");
	}
	fprintf (file, "</STACK>\n");
}

void stack_foreach (const wp_stack_t *s, wp_foreach_func_t f, void *data)
{
	int i;
	for (i = 0; i < (s->card); i++)
	{
		if (f (s->data[i], data) == false)
		{
			break;
		}
	}
}
