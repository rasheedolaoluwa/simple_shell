#include "shell.h"

/**
 * is_executable - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true (executable), 0 otherwise.
 */
int is_executable(info_passed *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * make_dup - Duplicates characters from a path string.
 * @pathstr: The PATH string.
 * @start: Starting index in pathstr.
 * @stop: Stopping index in pathstr.
 *
 * Return: Pointer to a new buffer with the duplicated path segment.
 */
char *make_dup(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, a = 0;

	for (a = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[a++] = pathstr[i];
	buf[a] = 0;
	return (buf);
}

/**
 * pathfinder - Finds the given command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *pathfinder(info_passed *info, char *pathstr, char *cmd)
{
	int i = 0, current_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && hay_checker(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = make_dup(pathstr, current_position, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(info, path))
				return (path);
			if (!pathstr[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}
