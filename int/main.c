#include <stdlib.h>
#include <stdio.h>

#include "int_vector_t.h"

int main(int argc, char *argv[])
{
	int_vector_t v;
	int_vector_initialize(&v);
	int i;
	for (i = 0; i < 20; i++)
	{
		int_vector_push_back(&v, i);
	}

	int_vector_t vcopy;
	int_vector_initialize(&vcopy);
	int_vector_copy(&vcopy, v);

	size_t length = int_vector_size(v);
	for (i = 0; i < length; i++)
	{
		printf("%d\n", int_vector_get(v, i));
	}

	printf("\nvcopy = \n");
	for (i = 0; i < int_vector_size(v); i++)
	{
		printf("%d\n", int_vector_get(v, i));
	}

	int_vector_clear(&v);
	printf("Printing a cleared vector:\n");
	length = int_vector_size(v);
	for (i = 0; i < length; i++)
	{
		printf("%d\n", int_vector_get(v, i));
	}

	printf("Empty? %u\n", int_vector_empty(v));

	int_vector_t v_array;
	int_vector_initialize(&v_array);
	int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	int_vector_assign_from_array(&v_array, arr, 10);
	printf("\nAssigned from array:\n");
	for (i = 0; i < int_vector_size(v_array); i++)
	{
		printf("%d\n", int_vector_get(v_array, i));
	}

	int_vector_uninitialize(v);
	int_vector_uninitialize(vcopy);
	return 0;
}
