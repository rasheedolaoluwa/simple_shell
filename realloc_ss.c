#include "shell.h"

/**
 * _memset - Fills memory with a constant byte
 * @s: Pointer to the memory area
 * @b: Byte to fill the memory area with
 * @n: Number of bytes to be filled
 * Return: Pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Frees a string of strings (array of strings)
 * @pp: Pointer to the array of strings
 */
void ffree(char **pp)
{
	char **temp = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(temp);
}

/**
 * _realloc - Reallocates a block of memory
 * @ptr: Pointer to the previously allocated memory
 * @old_size: Size in bytes of the previous block
 * @new_size: Size in bytes of the new block
 * Return: Pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	for (unsigned int i = 0; i < (old_size < new_size ? old_size : new_size); i++)
		new_ptr[i] = ((char *)ptr)[i];
	free(ptr);
	return (new_ptr);
}
