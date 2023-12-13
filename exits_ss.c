#include "shell.h"

/**
 * _strncpy - Copies a string
 * @dest: The destination string to be copied to
 * @src: The source string
 * @n: The number of characters to be copied
 * Return: The destination string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *start = dest;

	for (i = 0; src[i] != '\0' && i < n - 1; i++)
		dest[i] = src[i];

	for (j = i; j < n; j++)
		dest[j] = '\0';

	return (start);
}

/**
 * _strncat - Concatenates two strings
 * @dest: The first string
 * @src: The second string
 * @n: The maximum number of bytes to use from src
 * Return: The destination string
 */
char *_strncat(char *dest, char *src, int n)
{
	int dest_len = 0, src_index = 0;
	char *start = dest;

	while (dest[dest_len] != '\0')
		dest_len++;

	for (src_index = 0; src[src_index] != '\0' && src_index < n; src_index++)
		dest[dest_len++] = src[src_index];

	dest[dest_len] = '\0';

	return (start);
}

/**
 * _strchr - Locates a character in a string
 * @s: The string to be searched
 * @c: The character to look for
 * Return: Ptr to first occurrence of char c in the str s or NULL if not found
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}

	return (*s == c ? s : NULL);
}
