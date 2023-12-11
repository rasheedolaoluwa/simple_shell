#include "shell.h"

/**
 * _eputs - Prints an input string to stderr
 * @str: The string to be printed
 * Return: Nothing
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - Writes the character c to stderr
 * @c: The character to print
 * Return: On success 1. On error -1. and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int buf_index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, buf_index);
		buf_index = 0;
	}
	if (c != BUF_FLUSH)
		buffer[buf_index++] = c;
	return (1);
}

/**
 * _putfd - Writes the character c to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 * Return: On success 1. On error -1. and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int buf_index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, buf_index);
		buf_index = 0;
	}
	if (c != BUF_FLUSH)
		buffer[buf_index++] = c;
	return (1);
}

/**
 * _putsfd - Prints an input string to a given file descriptor
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 * Return: The number of characters put
 */
int _putsfd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		char_count += _putfd(*str++, fd);
	}
	return (char_count);
}