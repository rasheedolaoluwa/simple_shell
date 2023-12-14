#include "shell.h"

/**
 * intractive - Returns true if shell is in interactive mode
 * @inf: Struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int intractive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_delm - Checks if character is a delimiter
 * @m: Character to check
 * @delm: Delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delm(char m, char *delm)
{
	while (*delm)
		if (*delm++ == m)
			return (1);
	return (0);
}

/**
 * _isapha - Checks for alphabetic character
 * @m: Character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isapha(int m)
{
	if ((m >= 'a' && m <= 'z') || (m >= 'A' && m <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _ati - Converts a string to an integer
 * @str: String to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _ati(char *str)
{
	int r, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (r = 0; str[r] != '\0' && flag != 2; r++)
	{
		if (str[r] == '-')
			sign *= -1;

		if (str[r] >= '0' && str[r] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str[r] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
