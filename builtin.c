#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status (0) if info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exitcheck;
		return (-1);
	}
	info->err_num = 0;
	return (-1);
}

/**
 * _mycd - function that changes the current directory of the process
 * @info: structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
	{
		_puts("TODO: >>getcwd failure emsg here<<\n");
		return (1);
	}
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = _getenv(info, "PWD=");
		chdir_ret = chdir(dir ? dir : "/");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(dir), _putchar('\n');
		chdir_ret = chdir(dir);
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - function that displays help information.
 * @info: structure containing potential arguments.Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array = info->argv;

	_puts("help call works. Function not yet implemented \n");
	if (arg_array)
		_puts(*arg_array);
	return (0);
}
