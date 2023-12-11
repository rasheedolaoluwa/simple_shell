#include "shell.h"

/**
 * _strcpy - Copies a string to a destination
 * @dest: The destination buffer
 * @src: The source string
 * Return: Pointer to the destination buffer
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: The string to be duplicated
 * Return: Pointer to the duplicated string, or NULL on failure
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);
	while (str[length])
		length++;
	duplicate = malloc(sizeof(char) * (length + 1));
	if (!duplicate)
		return (NULL);
	for (int i = 0; i < length; i++)
		duplicate[i] = str[i];
	duplicate[length] = '\0';
	return (duplicate);
}

/**
 * _puts - Prints a string to stdout
 * @str: The string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes the character c to stdout
 * @c: The character to print
 * Return: 1 on success, -1 on error with errno set appropriately
 */
int _putchar(char c)
{
	static int buf_index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE)
	{
		write(1, buf, buf_index);
		buf_index = 0;
	}
	if (c != BUF_FLUSH)
		buf[buf_index++] = c;
	return (1);
}
