#include "shell.h"

/**
 * get_env - Returns the string array copy of our environment.
 * @info: Structure containing potential arguments.
 * Return: String array copy of the environment.
 */
char **get_env(info_passed *info)
{
	if (!info->environ || info->env_change)
	{
		info->environ = list_to_strings(info->env);
		info->env_change = 0;
	}

	return (info->environ);
}

/**
 * unset_env - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The string environment variable property.
 * Return: 1 on delete, 0 otherwise.
 */
int unset_env(info_passed *info, char *var)
{
	list_str *node = info->env;
	size_first i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = hay_checker(node->str, var);
		if (p && *p == '=')
		{
			info->env_change = delete_node(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_change);
}

/**
 * set_env - Initialize a new environment variable, or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The string environment variable property.
 * @value: The string environment variable value.
 * Return: Always 0.
 */
int set_env(info_passed *info, char *var, char *value)
{
	char *buf = NULL;
	list_str *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = hay_checker(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_change = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info’s->env_change = 1;
	return (0);
}
