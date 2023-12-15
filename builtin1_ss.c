#include "shell.h"

/**
 * shell_history - Displays the history list, one command per line, preceded
 *                 with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_history(info_passed *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Removes an alias.
 * @info: Parameter struct.
 * @str: The string alias to be removed.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_passed *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node(&(info->alias),
		get_index(info->alias, prefix_start(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Sets an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_passed *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_str *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_alias(info_passed *info)
{
	int i = 0;
	char *p = NULL;
	list_str *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(prefix_start(info->alias, info->argv[i], '='));
	}

	return (0);
}
