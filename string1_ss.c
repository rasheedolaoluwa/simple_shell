#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: String to measure.
 * Return: The length of the string.
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
 * @s1: First string for comparison.
 * @s2: Second string for comparison.
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 equals s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if a string starts with a given substring.
 * @haystack: String to search within.
 * @needle: Substring to look for.
 * Return: Pointer to the character in haystack after needle, or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string where src is appended.
 * @src: Source string to append to dest.
 * Return: Pointer to the concatenated string.
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
