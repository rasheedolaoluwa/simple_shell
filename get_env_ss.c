#include "shell.h"

/**
 * shell_env - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_env(info_passed *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * shell_get_env - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: The value of the environment variable.
 */
char *shell_get_env(info_passed *info, const char *name)
{
	list_str *node = info->env;
	char *p;

	while (node)
	{
		p = hay_checker(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * shell_setenv - Initializes a new environment variable,
 * or modifies an existing one.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_setenv(info_passed *info)
{
	if (info->argc != 3)
	{
		print_str("Incorrect number of arguments\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * shell_unsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_unsetenv(info_passed *info)
{
	int i;

	if (info->argc == 1)
	{
		print_str("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_env(info, info->argv[i]);

	return (0);
}

/**
 * populate_envlist - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int populate_envlist(info_passed *info)
{
	list_str *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
