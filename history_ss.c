#include "shell.h"

/**
 * get_history_file - Gets the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing history file path.
 */
char *get_history_file(info_passed *info)
{
	char *buf, *dir;

	dir = shell_get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Creates a file, or appends to an existing file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int write_history(info_passed *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_str *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		writes_fd(node->str, fd);
		write_fd('\n', fd);
	}
	write_fd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads history from file.
 * @info: The parameter struct.
 *
 * Return: history_count on success, 0 otherwise.
 */
int read_history(info_passed *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->history_count = linecount;
	while (info->history_count-- >= HIST_MAX)
		delete_node(&(info->history), 0);
	order_history(info);
	return (info->history_count);
}

/**
 * build_history_list - Adds entry to a history linked list.
 * @info: Structure containing potential arguments.
 * @buf: Buffer containing the history entry.
 * @linecount: The history line count.
 *
 * Return: Always 0.
 */
int build_history_list(info_passed *info, char *buf, int linecount)
{
	list_str *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * order_history - Renumbers the history linked list after changes.
 * @info: Structure containing potential arguments.
 *
 * Return: The new history_count.
 */
int order_history(info_passed *info)
{
	list_str *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->history_count = i);
}
