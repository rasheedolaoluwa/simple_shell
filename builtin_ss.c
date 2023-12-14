#include "shell.h"

/**
 * _ourexit - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: exits with a given exit status (0) if info->argv[0] != "exit"
 */
int _ourexit(info_t *inf)
{
	int exit_status;

	if (inf->argv[1])  /* If there is an exit argument */
	{
		exit_status = _erratoi(inf->argv[1]);
		if (exit_status == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = exit_status;
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _ourcd - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _ourcd(info_t *inf)
{
	char *str, *direc, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		direc = _getenv(inf, "HOME=");
		if (!direc)
			chdir_ret = chdir((direc = _getenv(inf, "PWD=")) ? direc : "/");
		else
			chdir_ret = chdir(direc);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((direc = _getenv(info, "OLDPWD=")) ? direc : "/");
	}
	else
		chdir_ret = chdir(inf->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _ourhelp - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _ourhelp(info_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
