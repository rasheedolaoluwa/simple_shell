#include "shell.h"

/**
 * _ourenv - Prints the current environment
 * @inf: Struct with potential args. Used to maintain const funct prototype.
 * Return: Always 0
 */
int _ourenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * _gtenv - Gets the value of an environment variable
 * @inf: Structure containing potential arguments.
 * @nme: Environment variable name
 * Return: The value of the environment variable
 */
char *_gtenv(info_t *inf, const char *nme)
{
	list_t *nde = inf->env;
	char *b;

	while (nde)
	{
		b = starts_with(nde->str, nme);
		if (b && *b == '=')
			return (b + 1);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * _orsetenv - Initialize a new environment variable, or modify an existing one
 * @inf: Struct with potential args. Used to maintain const funct prototype.
 * Return: Always 0
 */
int _orsetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _ourunsetenv - Remove an environment variable
 * @inf: Struct with potential args. Used to maintain const funct prototype.
 * Return: Always 0
 */
int _ourunsetenv(info_t *inf)
{
	int u;

	if (inf->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (u = 1; u < inf->argc; u++)
		_unsetenv(inf, inf->argv[u]);

	return (0);
}

/**
 * pop_env_list - Populates env linked list
 * @inf: Struct with potential args. Used to maintain const funct prototype.
 * Return: Always 0
 */
int pop_env_list(info_t *inf)
{
	list_t *nde = NULL;
	size_t u;

	for (u = 0; environ[u]; u++)
		add_node_end(&nde, environ[u], 0);
	inf->env = nde;
	return (0);
}
