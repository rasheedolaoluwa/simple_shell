#include "shell.h"

/**
 * free_n_null - Frees a pointer and sets the address to NULL.
 * @ptr: Address of the pointer to be freed.
 *
 * Return: 1 if the pointer is successfully freed, otherwise 0.
 */
int free_n_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
