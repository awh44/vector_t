#ifndef _VECTOR_T_H_
#define _VECTOR_T_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


static const size_t VECTOR_NOT_FOUND = SIZE_MAX;
static unsigned short vector_is_power_two(size_t value)
{
	return (value != 0) && ((value & (value - 1)) == 0);
}

#define MAKE_VECTOR_H(name, type)\
typedef struct name##_t name##_t;\
name##_t *name##_initialize_with_capacity(size_t capacity);\
name##_t *name##_initialize(void);\
void name##_uninitialize(name##_t *vector);\
void name##_copy(name##_t *dest, name##_t *src);\
void name##_assign_from_array(name##_t *dest, type *array, size_t size);\
int name##_compare(const void *voida, const void *voidb);\
size_t name##_size(name##_t *vector);\
void name##_resize(name##_t *vector, size_t size);\
unsigned short name##_empty(name##_t *vector);\
type name##_get(name##_t *vector, size_t i);\
void name##_set(name##_t *vector, size_t i, type value);\
void name##_insert(name##_t *vector, type value, size_t position);\
void name##_remove(name##_t *vector, size_t position);\
void name##_push_back(name##_t *vector, type value);\
void name##_pop_back(name##_t *vector);\
void name##_clear(name##_t *vector);\
size_t name##_find_from(name##_t *vector, type value, size_t position);\
size_t name##_find(name##_t *vector, type value);\
unsigned short name##_contains(name##_t *vector, type value);\
type *name##_c_array(name##_t *vector);\
size_t name##_get_capacity(name##_t *vector);\


#define MAKE_VECTOR_C(name, type)\
struct name##_t\
{\
	type *array;\
	size_t elements;\
	size_t capacity; \
};\
\
static void name##_size_at_least(name##_t *vector, size_t needed_size);\
\
name##_t *name##_initialize_with_capacity(size_t capacity)\
{\
	name##_t *vector = malloc(sizeof *vector);\
	if (vector == NULL)\
	{\
		return NULL;\
	}\
\
	vector->array = malloc(capacity * sizeof *vector->array);\
	if (vector->array == NULL)\
	{\
		free(vector);\
		return NULL;\
	}\
\
	vector->elements = 0;\
	vector->capacity = capacity;\
	\
	return vector;\
}\
\
name##_t *name##_initialize(void)\
{\
	return name##_initialize_with_capacity(1);\
}\
\
void name##_uninitialize(name##_t *vector)\
{\
	free(vector->array);\
	free(vector);\
}\
\
\
void name##_copy(name##_t *destination, name##_t *source)\
{\
	name##_size_at_least(destination, source->elements);\
	memcpy(destination->array, source->array, source->elements * sizeof *source->array);\
	destination->elements = source->elements;\
}\
\
void name##_assign_from_array(name##_t *destination, type *array, size_t size)\
{\
	name##_size_at_least(destination, size);\
	memcpy(destination->array, array, size * sizeof *array);\
	destination->elements = size;\
}\
\
int name##_compare(const void *voida, const void *voidb)\
{\
	name##_t *a = (name##_t *) voida;\
	name##_t *b = (name##_t *) voidb;\
	if (a->elements < b->elements)\
	{\
		return -1;\
	}\
\
	if (a->elements > b->elements)\
	{\
		return 1;\
	}\
\
	printf("Doing memcmp...(a->elements = %zu, b->elements = %zu)\n", a->elements, b->elements);\
	return memcmp(a->array, b->array, a->elements * sizeof *a->array);\
}\
\
size_t name##_size(name##_t *vector)\
{\
	return vector->elements;\
}\
\
void name##_resize(name##_t *vector, size_t size)\
{\
	vector->array = realloc(vector->array, size * sizeof *vector->array);\
	vector->elements = size < vector->elements ? size : vector->elements;\
	vector->capacity = size;\
}\
\
unsigned short name##_empty(name##_t *vector)\
{\
	return vector->elements == 0;\
}\
\
type name##_get(name##_t *vector, size_t i)\
{\
	return vector->array[i];\
}\
\
void name##_set(name##_t *vector, size_t i, type value)\
{\
	vector->array[i] = value;\
}\
\
void name##_insert(name##_t *vector, type value, size_t position)\
{\
	name##_size_at_least(vector, vector->elements + 1);\
	memmove(vector->array + position + 1, vector->array + position, (vector->elements - position) * sizeof *vector->array);\
	vector->array[position] = value;\
	vector->elements++;\
}\
\
void name##_remove(name##_t *vector, size_t position)\
{\
	memmove(vector->array + position, vector->array + position + 1, (vector->elements - position) * sizeof *vector->array);\
	vector->elements--;\
}\
\
void name##_push_back(name##_t *vector, type value)\
{\
	size_t new_elements = vector->elements + 1;\
	name##_size_at_least(vector, new_elements);\
	vector->array[vector->elements] = value;\
	vector->elements = new_elements;\
}\
\
void name##_pop_back(name##_t *vector)\
{\
	vector->elements--;\
}\
\
void name##_clear(name##_t *vector)\
{\
	name##_resize(vector, 1);\
	vector->elements = 0;\
}\
\
size_t name##_find_from(name##_t *vector, type value, size_t position)\
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
size_t name##_find(name##_t *vector, type value)\
{\
	return name##_find_from(vector, value, 0);\
}\
\
unsigned short name##_contains(name##_t *vector, type value)\
{\
	return (name##_find(vector, value) != VECTOR_NOT_FOUND) || (vector->elements == SIZE_MAX && vector->array[SIZE_MAX] == value);\
}\
\
type *name##_c_array(name##_t *vector)\
{\
	return vector->array;\
}\
\
size_t name##_get_capacity(name##_t *vector)\
{\
	return vector->capacity;\
}\
\
static void name##_size_at_least(name##_t *vector, size_t needed_size)\
{\
	if (needed_size > vector->capacity)\
	{\
		size_t new_size = 2 * vector->capacity;\
		while (new_size < needed_size)\
		{\
			new_size *= 2;\
		}\
		name##_resize(vector, new_size);\
	}\
}

#endif
