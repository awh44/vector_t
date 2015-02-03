#include <stddef.h>

struct int_vector_t
{
	int *array;
	size_t elements;
	size_t size; 
};
typedef struct int_vector_t* int_vector_t;

void int_vector_initialize(int_vector_t *vector);
void int_vector_initialize_with_size(int_vector_t *vector, size_t size);
void int_vector_uninitialize(int_vector_t vector);
void int_vector_copy(int_vector_t *destination, int_vector_t source);
size_t int_vector_size(int_vector_t vector);
void int_vector_resize(int_vector_t *vector, size_t size);
unsigned short int_vector_empty(int_vector_t vector);
int int_vector_get(int_vector_t vector, size_t i);
void int_vector_set(int_vector_t vector, size_t i, int value);
void int_vector_push_back(int_vector_t *vector, int value);
void int_vector_clear(int_vector_t *vector);