#include "shell.h"

/**
 * _epts - Prints an input string to stderr
 * @string: The string to be printed
 * Return: Nothing
 */
void _epts(char *string)
{
	int indx = 0;

	if (!string)
		return;
	while (string[indx] != '\0')
	{
		_eptchar(string[indx]);
		indx++;
	}
}

/**
 * _eptchar - Writes the character c to stderr
 * @m: The character to print
 * Return: On success 1. On error -1. and errno is set appropriately.
 */
int _eptchar(char m)
{
	static int buff_index;
	static char buf[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || buff_index >= WRITE_BUF_SIZE)
	{
		write(2, buf, buff_index);
		buff_index = 0;
	}
	if (m != BUF_FLUSH)
		buf[buff_index++] = m;
	return (1);
}

/**
 * _putfdes - Writes the character c to a given file descriptor
 * @m: The character to print
 * @fdes: The file descriptor to write to
 * Return: On success 1. On error -1. and errno is set appropriately.
 */
int _putfdes(char m, int fdes)
{
	static int buff_index;
	static char buf[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || buff_index >= WRITE_BUF_SIZE)
	{
		write(fdes, buf, buff_index);
		buff_index = 0;
	}
	if (m != BUF_FLUSH)
		buf[buff_index++] = m;
	return (1);
}

/**
 * _putsfdes - Prints an input string to a given file descriptor
 * @string: The string to be printed
 * @fdes: The file descriptor to write to
 * Return: The number of characters put
 */
int _putsfdes(char *string, int fdes)
{
	int char_cnt = 0;

	if (!string)
		return (0);
	while (*string)
	{
		char_cnt += _putfdes(*string++, fdes);
	}
	return (char_cnt);
}
