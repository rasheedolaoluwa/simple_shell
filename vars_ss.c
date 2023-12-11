#include "shell.h"

/**
 * is_chain - Checks if current char in buffer is a command chaining delimiter
 * @info: Structure containing shell information and parameters
 * @buf: Buffer containing the current command or input string
 * @p: Pointer to the current position in the buffer
 *
 * Return: (1) if a chaining delimiter is found, (0) otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t current_pos = *p;

	if (buf[current_pos] == '|' && buf[current_pos + 1] == '|')
	{
		buf[current_pos] = '\0';
		current_pos++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[current_pos] == '&' && buf[current_pos + 1] == '&')
	{
		buf[current_pos] = '\0';
		current_pos++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[current_pos] == ';') /* End of command */
	{
		buf[current_pos] = '\0'; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = current_pos;
	return (1);
}

/**
 * check_chain - Determines if command chaining should continue based on
 *               the last command's status
 * @info: Structure containing shell information and parameters
 * @buf: Buffer containing the current command or input string
 * @p: Pointer to the current position in the buffer
 * @i: Starting position in the buffer for the current command
 * @len: Total length of the buffer
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t current_pos = *p;

	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[i] = '\0';
		current_pos = len;
	}
	else if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[i] = '\0';
		current_pos = len;
	}
	*p = current_pos;
}


/**
 * replace_alias - Replaces aliases in tokenized string with actual values
 * @info: Structure containing shell information and parameters
 *
 * Return: (1) if any alias is replaced, (0) otherwise
 */
int replace_alias(info_t *info)
{
	int index;
	list_t *node;
	char *alias_value;

	for (index = 0; index < 10; index++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		alias_value = strchr(node->str, '=');
		if (!alias_value)
			return (0);

		alias_value = strdup(alias_value + 1);
		if (!alias_value)
			return (0);

		info->argv[0] = alias_value;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string with their values
 * @info: Structure containing shell information and parameters
 *
 * Return: (1) if any variable is replaced, (0) otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	while (info->argv[i])
	{
		if (info’s argv[i][0] != '$' || !info->argv[i][1])
		{
			i++;
			continue;
		}

		/* Replace special variables $? and $$ */
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&info->argv[i],
				_strdup(convert_number(info->status, 10, 0)));
			i++;
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&info->argv[i],
				_strdup(convert_number(getpid(), 10, 0)));
			i++;
			continue;
		}

		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&info->argv[i],
				_strdup(_strchr(node->str, '=') + 1));
			i++;
			continue;
		}

		replace_string(&info->argv[i], _strdup(""));
		i++;
	}
	return (0);
}

/**
 * replace_string - Replaces a string with a new value
 * @old: Pointer to the original string
 * @new: The new string to replace with
 *
 * Return: (1) if replacement is successful, (0) otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
