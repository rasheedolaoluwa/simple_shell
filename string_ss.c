#include "shell.h"

/**
 * _strlen - Returns the length of a string
 * @s: String whose length is to be measured
 * Return: The length of the string
 */
int _strlen(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;
	return (length);
}

/**
 * _strcmp - Compares two strings lexicographically
 * @s1: First string for comparison
 * @s2: Second string for comparison
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
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
	return (*s1 == *s2 ? 0 : (*s1 < *s2 ? -1 : 1));
}

/**
 * starts_with - Checks if one string starts with another
 * @haystack: String to be searched
 * @needle: Substring to search for in haystack
 * Return: Address of next char in haystack after needle or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings
 * @dest: Destination buffer for the concatenated result
 * @src: Source string to append to dest
 * Return: Pointer to the concatenated string
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (ret);
}
