#include "shell.h"

/**
 * get_environ - Returns the string array copy of our environment
 * @info: Struct with potential args. Used to maintain const funct prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Struct with potential args. Used to maintain const funct prototype.
 * @var: The string env variable property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *position;

	if (!node || !var)
		return (0);

	while (node)
	{
		position = starts_with(node->str, var);
		if (position && *position == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable, or modify an existing one
 * @info: Struct with potential args. Used to maintain const funct prototype.
 * @var: The string env variable property
 * @value: The string env variable value
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *position;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);

	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;

	while (node)
	{
		position = starts_with(node->str, var);
		if (position && *position == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
