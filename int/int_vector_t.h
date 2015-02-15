#include <stddef.h>

struct int_vector_t
{
	int *array;
	size_t elements;
	size_t capacity; 
};
typedef struct int_vector_t int_vector_t;

extern const size_t VECTOR_NOT_FOUND;

void int_vector_initialize(int_vector_t *vector);
void int_vector_initialize_with_capacity(int_vector_t *vector, size_t capacity);
void int_vector_uninitialize(int_vector_t *vector);
void int_vector_copy(int_vector_t *destination, int_vector_t *source);
void int_vector_assign_from_array(int_vector_t *destination, int *array, size_t size);
size_t int_vector_size(int_vector_t *vector);
void int_vector_resize(int_vector_t *vector, size_t size);
unsigned short int_vector_empty(int_vector_t *vector);
int int_vector_get(int_vector_t *vector, size_t i);
void int_vector_set(int_vector_t *vector, size_t i, int value);
void int_vector_insert(int_vector_t *vector, int value, size_t position);
void int_vector_remove(int_vector_t *vector, size_t position);
void int_vector_push_back(int_vector_t *vector, int value);
void int_vector_pop_back(int_vector_t *vector);
void int_vector_clear(int_vector_t *vector);
size_t int_vector_find_from(int_vector_t *vector, int value, size_t position);
size_t int_vector_find(int_vector_t *vector, int value);
unsigned short int_vector_contains(int_vector_t *vector, int value);
