#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: Pointer to the string whose length is to be determined.
 *
 * Return: The length of the string as an integer.
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @a1: First string for comparison.
 * @a2: Second string for comparison.
 *
 * Return: Negative if a1 < a2, positive if a1 > a2, zero if a1 == a2.
 */
int _strcmp(char *a1, char *a2)
{
	while (*a1 && *a2)
	{
		if (*a1 != *a2)
			return (*a1 - *a2);
		a1++;
		a2++;
	}
	return (*a1 == *a2) ? 0 : (*a1 < *a2 ? -1 : 1);
}

/**
 * hay_checker - Checks if a string starts with a specified substring.
 * @haystack: String to be searched.
 * @needle: Substring to find in the haystack.
 *
 * Return: Address of next character in haystack if needle is found, or NULL.
 */
char *hay_checker(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination buffer where the source string is appended.
 * @src: Source string to be appended to the destination.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
