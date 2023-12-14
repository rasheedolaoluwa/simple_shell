#include "shell.h"

/**
 * _errati - Converts a string to an integer.
 * @str: String to convert.
 * Return: Converted integer, 0 if no numbers, -1 on error.
 */
int _errati(char *str)
{
	int u = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (u = 0;  str[u] != '\0'; u++)
	{
		if (str[u] >= '0' && str[u] <= '9')
		{
			res *= 10;
			res += (str[u] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * prnt_error - Prints an error message.
 * @inf: Info struct containing shell state.
 * @est: Error message to print.
 * Return: Void.
 */
void prnt_error(info_t *inf, char *est)
{
	_eputs(inf->fname);
	_eputs(": ");
	prnt_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(est);
}

/**
 * prnt_d - Prints an integer in decimal format.
 * @inpt: Number to print.
 * @fdes: File descriptor to write to.
 * Return: Number of characters printed.
 */
int prnt_d(int inpt, int fdes)
{
	int (*__putchar)(char) = _putchar;
	int u, cnt = 0;
	unsigned int _abs_, current;

	if (fdes == STDERR_FILENO)
		__putchar = _eputchar;
	if (inpt < 0)
	{
		_abs_ = -inpt;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = inpt;
	current = _abs_;
	for (u = 1000000000; u > 1; u /= 10)
	{
		if (_abs_ / u)
		{
			__putchar('0' + current / u);
			cnt++;
		}
		current %= u;
	}
	__putchar('0' + current);
	cnt++;

	return (cnt);
}

/**
 * covrt_number - Converts a number to a string in specified base.
 * @num: Number to convert.
 * @bas: Base for conversion.
 * @flags: Flags to determine conversion behavior.
 * Return: Converted number as string.
 */
char *covrt_number(long int num, int bas, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % bas];
		n /= bas;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - Removes comments from a string.
 * @buffer: String to remove comments from.
 * Return: Always 0.
 */
void rm_comments(char *buffer)
{
	int u;

	for (u = 0; buffer[u] != '\0'; u++)
		if (buffer[u] == '#' && (!u || buffer[u - 1] == ' '))
		{
			buffer[u] = '\0';
			break;
		}
}
