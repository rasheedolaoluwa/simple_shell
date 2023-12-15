#include "shell.h"

/**
 * shell_exit - Exits the shell.
 * @info: Structure containing potential arguments.
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit".
 */
int shell_exit(info_passed *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			print_str(info->argv[1]);
			write_char('\n');
			return (1);
		}
		info->error_code = _erratoi(info->argv[1]);
		return (-2);
	}
	info->error_code = -1;
	return (-2);
}

/**
 * shell_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_cd(info_passed *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("Failed! No such directory");
	if (!info->argv[1])
	{
		dir = shell_get_env(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = shell_get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!shell_get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(shell_get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = shell_get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Cd not exist");
		print_str(info->argv[1]), write_char('\n');
	}
	else
	{
		set_env(info, "OLDPWD", shell_get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shell_help - Displays help information for the shell.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_help(info_passed *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help Function\n");
	if (0)
		_puts(*arg_array);
	return (0);
}
