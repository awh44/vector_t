#include <stdlib.h>
#include <stdio.h>

#include "vector_t.h"
MAKE_VECTOR_TYPE(int)
MAKE_VECTOR_TYPE(char);

void print_vector(int_vector_t *vector)
{
	size_t i;
	for (i = 0; i < int_vector_size(vector); i++)
	{
		printf("%d\n", int_vector_get(vector, i));
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please include which vector type to test ('i' for int, 'c' for character).\n");
		return;
	}

	if (argv[1][0] == 'i')
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
		int_vector_copy(&vcopy, &v);
		printf("v.capacity = %zu, vcopy.capacity = %zu\n", v.capacity, vcopy.capacity);

		print_vector(&v);

		printf("\nvcopy = \n");
		print_vector(&vcopy);
		int_vector_pop_back(&vcopy);
		
		printf("pop_back'd vcopy:\n");
		print_vector(&vcopy);
		
		int_vector_pop_back(&vcopy);
		int_vector_pop_back(&vcopy);
		int_vector_pop_back(&vcopy);
		printf("pop_back'd three more times:\n");
		print_vector(&vcopy);


		int_vector_insert(&v, 1000, 8);
		printf("Added 1000 at position 8 of v:\n");
		print_vector(&v);
		
		int_vector_remove(&v, 0);
		printf("Removed first element of v:\n");
		print_vector(&v);

		int_vector_clear(&v);
		printf("Printing a cleared vector:\n");
		print_vector(&v);	

		printf("Empty? %u\n", int_vector_empty(&v));

		int_vector_t v_array;
		int_vector_initialize(&v_array);
		int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		int_vector_assign_from_array(&v_array, arr, 10);
		printf("\nAssigned from array:\n");
		print_vector(&v_array);

		printf("v_array contains 0? %u\n", int_vector_contains(&v_array, 0));
		printf("Position of 4 in v_array: %zu\n", int_vector_find(&v_array, 4));
		printf("Position of 25 in v_array: %zu\n", int_vector_find(&v_array, 25));
		printf("v_array contains 28183? %u\n", int_vector_contains(&v_array, 28183));

		int_vector_uninitialize(&v);
		int_vector_uninitialize(&vcopy);
		int_vector_uninitialize(&v_array);
	}
	else if (argv[1][0] == 'c')
	{
		char_vector_t c, c_copy, c_goodbye;
		char_vector_initialize(&c);
		char_vector_initialize(&c_copy);
		char_vector_initialize(&c_goodbye);

		char_vector_assign_from_array(&c, "Hello!" + 1, strlen("Hello!"));
		char_vector_copy(&c_copy, &c);
		char_vector_assign_from_array(&c_goodbye, "Goodbye", strlen("Goodbye"));

		printf("%s\n", c.array);
		printf("%s\n", c_copy.array);
		printf("%.*s\n", c_goodbye.elements, c_goodbye.array);
		printf("%d\n", char_vector_compare(&c, &c_copy));
		printf("%d\n", char_vector_compare(&c, &c_goodbye));
		printf("%d\n", char_vector_compare(&c_goodbye, &c));

		char *c_array = char_vector_c_array(&c);
		{
			size_t i;
			for (i = 0; i < char_vector_size(&c); i++)
			{
				printf("%c\n", c_array[i]);
			}
		}

		char_vector_uninitialize(&c);
		char_vector_uninitialize(&c_copy);
		char_vector_uninitialize(&c_goodbye);
	}
	else
	{
		printf("That test type is unknown. Please use 'i' or 'c'.\n");
		return 1;
	}

	return 0;
}
