#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


const size_t VECTOR_NOT_FOUND = SIZE_MAX;
unsigned short vector_is_power_two(size_t value)
{
	return (value != 0) && ((value & (value - 1)) == 0);
}

#define MAKE_VECTOR_TYPE(type)\
typedef struct\
{\
	type *array;\
	size_t elements;\
	size_t capacity; \
} type##_vector_t;\
\
void type##_vector_size_at_least(type##_vector_t *vector, size_t needed_size);\
\
void type##_vector_initialize_with_capacity(type##_vector_t *vector, size_t capacity)\
{\
	vector->array = malloc(capacity * sizeof *vector->array);\
	vector->elements = 0;\
	vector->capacity = capacity;\
}\
\
void type##_vector_initialize(type##_vector_t *vector)\
{\
	type##_vector_initialize_with_capacity(vector, 1);\
}\
\
void type##_vector_copy(type##_vector_t *destination, type##_vector_t *source)\
{\
	type##_vector_size_at_least(destination, source->elements);\
	memcpy(destination->array, source->array, source->elements * sizeof *source->array);\
	destination->elements = source->elements;\
}\
\
void type##_vector_assign_from_array(type##_vector_t *destination, type *array, size_t size)\
{\
	type##_vector_size_at_least(destination, size);\
	memcpy(destination->array, array, size * sizeof *array);\
	destination->elements = size;\
}\
\
void type##_vector_uninitialize(type##_vector_t *vector)\
{\
	free(vector->array);\
}\
\
size_t type##_vector_size(type##_vector_t *vector)\
{\
	return vector->elements;\
}\
\
void type##_vector_resize(type##_vector_t *vector, size_t size)\
{\
	vector->array = realloc(vector->array, size * sizeof *vector->array);\
	vector->elements = size < vector->elements ? size : vector->elements;\
	vector->capacity = size;\
}\
\
unsigned short type##_vector_empty(type##_vector_t *vector)\
{\
	return vector->elements == 0;\
}\
\
type type##_vector_get(type##_vector_t *vector, size_t i)\
{\
	return vector->array[i];\
}\
\
void type##_vector_set(type##_vector_t *vector, size_t i, type value)\
{\
	vector->array[i] = value;\
}\
\
void type##_vector_insert(type##_vector_t *vector, type value, size_t position)\
{\
	type##_vector_size_at_least(vector, vector->elements + 1);\
	memmove(vector->array + position + 1, vector->array + position, (vector->elements - position) * sizeof *vector->array);\
	vector->array[position] = value;\
	vector->elements++;\
}\
\
void type##_vector_remove(type##_vector_t *vector, size_t position)\
{\
	memmove(vector->array + position, vector->array + position + 1, (vector->elements - position) * sizeof *vector->array);\
	vector->elements--;\
}\
\
void type##_vector_push_back(type##_vector_t *vector, type value)\
{\
	size_t new_elements = vector->elements + 1;\
	type##_vector_size_at_least(vector, new_elements);\
	vector->array[vector->elements] = value;\
	vector->elements = new_elements;\
}\
\
void type##_vector_pop_back(type##_vector_t *vector)\
{\
	vector->elements--;\
}\
\
void type##_vector_clear(type##_vector_t *vector)\
{\
	type##_vector_resize(vector, 1);\
	vector->elements = 0;\
}\
\
size_t type##_vector_find_from(type##_vector_t *vector, type value, size_t position)\
{\
	size_t i;\
	for (i = position; i < vector->elements; i++)\
	{\
		if (vector->array[i] == value)\
		{\
			return i;\
		}\
	}\
\
	return VECTOR_NOT_FOUND;\
}\
\
size_t type##_vector_find(type##_vector_t *vector, type value)\
{\
	return type##_vector_find_from(vector, value, 0);\
}\
\
unsigned short type##_vector_contains(type##_vector_t *vector, type value)\
{\
	return (type##_vector_find(vector, value) != VECTOR_NOT_FOUND) || (vector->elements == SIZE_MAX && vector->array[SIZE_MAX] == value);\
}\
\
void type##_vector_size_at_least(type##_vector_t *vector, size_t needed_size)\
{\
	if (needed_size > vector->capacity)\
	{\
		size_t new_size = 2 * vector->capacity;\
		while (new_size < needed_size)\
		{\
			new_size *= 2;\
		}\
		type##_vector_resize(vector, new_size);\
	}\
}
