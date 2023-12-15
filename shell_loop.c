#include "shell.h"

/**
 * hshell - Main shell loop.
 * @info: The parameter and return information struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or specific error code.
 */
int hshell(info_passed *info, char **av)
{
	ssize_t a = 0;
	int builtin_ret = 0;

	while (a != -1 && builtin_ret != -2)
	{
		info_start(info);
		if (is_interactive(info))
			_puts("$ ");
		write_char(BUFFER_FLUSH);
		a = get_input(info);
		if (a != -1)
		{
			set_info(info, av);
			builtin_ret = builtin_search(info);
			if (builtin_ret == -1)
				cmd_search(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		info_end(info, 0);
	}
	write_history(info);
	info_end(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}
	return (builtin_ret);
}

/**
 * builtin_search - Finds a builtin command.
 * @info: The parameter and return information struct.
 *
 * Return: -1 if builtin not found, 0 if executed successfully,
 *         1 if found but not successful, -2 if builtin signals exit().
 */
int builtin_search(info_passed *info)
{
	int i, built_in_ret = -1;
	shell_builtin builtintbl[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->error_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * cmd_search - Finds a command in PATH.
 * @info: The parameter and return information struct.
 *
 * Return: void.
 */
void cmd_search(info_passed *info)
{
	char *path = NULL;
	int a, b;

	info->path = info->argv[0];
	if (info->count_line == 1)
	{
		info->error_count++;
		info->count_line = 0;
	}
	for (a = 0, b = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = pathfinder(info, shell_get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		shell_fork(info);
	}
	else
	{
		if ((is_interactive(info) || shell_get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && is_executable(info, info->argv[0]))
			shell_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * shell_fork - Forks a process to execute a command.
 * @info: The parameter and return information struct.
 *
 * Return: void.
 */
void shell_fork(info_passed *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: Execution Failed!");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env(info)) == -1)
		{
			info_end(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
