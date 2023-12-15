#include "shell.h"

/**
 * _strcpy - Copies the content of one string to another.
 * @dest: The buffer where the content is copied to.
 * @src: The source string to copy.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - Creates a duplicate of the provided string.
 * @str: The string to be duplicated.
 *
 * Return: Pointer to the newly allocated duplicate string,
 * or NULL if memory allocation fails.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *dupli;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	dupli = malloc(sizeof(char) * (length + 1));
	if (!dupli)
		return (NULL);
	for (length++; length--;)
		dupli[length] = *--str;
	return (dupli);
}

/**
 * _puts - Prints a string to the standard output.
 * @str: The string to be printed.
 *
 * Return: None. Function is void.
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes a single character to the standard output.
 * @c: The character to print.
 *
 * Return: 1 on success. On error, returns -1, and errno is set appropriately.
 */
int _putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUFFER_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}
