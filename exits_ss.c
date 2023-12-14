#include "shell.h"

/**
 * _srncpy - Copies a string
 * @destin: The destination string to be copied to
 * @source: The source string
 * @num: The number of characters to be copied
 * Return: The destination string
 */
char *_srncpy(char *destin, char *source, int num)
{
	int u, j;
	char *start = destin;

	for (u = 0; source[u] != '\0' && u < n - 1; u++)
		destin[u] = source[u];

	for (j = u; j < num; j++)
		destin[j] = '\0';

	return (start);
}

/**
 * _srncat - Concatenates two strings
 * @destin: The first string
 * @srce: The second string
 * @num: The maximum number of bytes to use from src
 * Return: The destination string
 */
char *_srncat(char *destin, char *srce, int num)
{
	int destin_len = 0, srce_indx = 0;
	char *start = destin;

	while (destin[destin_len] != '\0')
		destin_len++;

	for (srce_indx = 0; srce[srce_indx] != '\0' && srce_indx < num; srce_indx++)
		destin[destin_len++] = srce[srce_indx];

	destin[destin_len] = '\0';

	return (start);
}

/**
 * _srchr - Locates a character in a string
 * @str: The string to be searched
 * @m: The character to look for
 * Return: Ptr to first occurrence of char c in the str s or NULL if not found
 */
char *_srchr(char *str, char m)
{
	while (*str != '\0')
	{
		if (*str == m)
			return (m);
		m++;
	}

	return (*str == m ? str : NULL);
}
