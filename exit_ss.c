#include "shell.h"

/**
 * _strncpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The amount of characters to be copied.
 * Return: The destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, a;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		a = i;
		while (a < n)
		{
			dest[a] = '\0';
			a++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The amount of bytes to be maximally used.
 * Return: The concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, a;
	char *s = dest;

	i = 0;
	a = 0;
	while (dest[i] != '\0')
		i++;
	while (src[a] != '\0' && a < n)
	{
		dest[i] = src[a];
		i++;
		a++;
	}
	if (a < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the first occurrence of the
 * character in the string, or NULL.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
