#include "shell.h"

/**
 * _ourhistory - Displays shell command history with line numbers.
 * @inf: Contains arguments and shell information.
 * Return: 0 (success)
 */
int _ourhistory(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * unst_alias - Removes an alias if it exists.
 * @inf: Shell information and arguments.
 * @string: Alias to be removed.
 * Return: 0 (success), 1 (error)
 */
int unst_alias(info_t *inf, char *string)
{
	char *b, m;
	int retu;

	b = _strchr(string, '=');
	if (!b)
		return (1);
	m = *b;
	*b = 0;
	retu = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, string, -1)));
	*b = m;
	return (retu);
}

/**
 * st_alias - Sets or updates an alias.
 * @inf: Shell information and arguments.
 * @string: Alias to be set or updated.
 * Return: 0 (success), 1 (error)
 */
int st_alias(info_t *inf, char *string)
{
	char *b;

	b = _strchr(string, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unst_alias(inf, string));

	unst_alias(inf, string);
	return (add_node_end(&(inf->alias), string, 0) == NULL);
}

/**
 * prnt_alias - Prints a single alias.
 * @nde: Alias node to be printed.
 * Return: 0 (success), 1 (error)
 */
int prnt_alias(list_t *nde)
{
	char *b = NULL, *a = NULL;

	if (nde)
	{
		b = _strchr(nde->string, '=');
		for (a = nde->string; a <= b; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _ouralias - Mimics the 'alias' command, printing or setting aliases.
 * @inf: Shell information and arguments.
 * Return: 0 (success)
 */
int _ouralias(info_t *inf)
{
	int i = 0;
	char *b = NULL;
	list_t *nde = NULL;

	if (inf->argc == 1)
	{
		nde = inf->alias;
		while (nde)
		{
			prnt_alias(nde);
			nde = nde->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		b = _strchr(inf->argv[i], '=');
		if (b)
			st_alias(inf, inf->argv[i]);
		else
			prnt_alias(node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
