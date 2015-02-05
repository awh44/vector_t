#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "int_vector_t.h"

void int_vector_size_at_least(int_vector_t *vector, size_t needed_size);

void int_vector_initialize(int_vector_t *vector)
{
	int_vector_initialize_with_size(vector, 1);
}

void int_vector_initialize_with_size(int_vector_t *vector, size_t size)
{
	*vector = malloc(sizeof **vector);
	(*vector)->array = malloc(size * sizeof *(*vector)->array);
	(*vector)->elements = 0;
	(*vector)->size = size;
}

void int_vector_copy(int_vector_t *destination, int_vector_t source)
{
	if ((*destination)->size < source->elements)
	{
		int_vector_resize(destination, source->elements);
	}

	memcpy((*destination)->array, source->array, source->elements);
}

void int_vector_assign_from_array(int_vector_t *destination, int *array, size_t size)
{
	int_vector_size_at_least(destination, size);
	memcpy((*destination)->array, array, size * sizeof *array);
	(*destination)->elements = size;
}

void int_vector_uninitialize(int_vector_t vector)
{
	free(vector->array);
	free(vector);
}

size_t int_vector_size(int_vector_t vector)
{
	return vector->elements;
}

void int_vector_resize(int_vector_t *vector, size_t size)
{
	(*vector)->array = realloc((*vector)->array, size * sizeof *(*vector)->array);
	(*vector)->elements = size < (*vector)->elements ? size : (*vector)->elements;
	(*vector)->size = size;
}

unsigned short int_vector_empty(int_vector_t vector)
{
	return vector->elements == 0;
}

int int_vector_get(int_vector_t vector, size_t i)
{
	return vector->array[i];
}

void int_vector_set(int_vector_t vector, size_t i, int value)
{
	vector->array[i] = value;
}

void int_vector_push_back(int_vector_t *vector, int value)
{
	size_t new_elements = (*vector)->elements + 1;
	int_vector_size_at_least(vector, new_elements);
	(*vector)->array[(*vector)->elements] = value;
	(*vector)->elements = new_elements;
}

void int_vector_clear(int_vector_t *vector)
{
	int_vector_resize(vector, 1);
	(*vector)->elements = 0;
}

void int_vector_size_at_least(int_vector_t *vector, size_t needed_size)
{
	if (needed_size > (*vector)->size)
	{
		size_t new_size = 2 * (*vector)->size;
		while (new_size < needed_size)
		{
			new_size *= 2;
		}
		int_vector_resize(vector, new_size);
	}
}
