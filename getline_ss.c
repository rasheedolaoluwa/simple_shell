#include "shell.h"

/**
 * input_buf - Buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of buffer.
 * @len: Address of length variable.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_passed *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, signal_handler);
#if USE_GETLINE
		a = getline(buf, &len_p, stdin);
#else
		a = _getline(info, buf, &len_p);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0'; /* remove trailing newline */
				a--;
			}
			info->count_line = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->history_count++);
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - Gets a line minus the newline.
 * @info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_passed *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, a, len;
	ssize_t b = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFFER_FLUSH);
	b = input_buf(info, &buf, &len);
	if (b == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		a = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &a, i, len);
		while (a < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &a))
				break;
			a++;
		}

		i = a + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (b); /* return length of buffer from _getline() */
}

/**
 * read_buf - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer to read into.
 * @i: Pointer to size variable.
 *
 * Return: Number of bytes read.
 */
ssize_t read_buf(info_passed *info, char *buf, size_t *i)
{
	ssize_t b = 0;

	if (*i)
		return (0);
	b = read(info->readfd, buf, READ_BUF_SIZE);
	if (b >= 0)
		*i = b;
	return (b);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Number of bytes in the line.
 */
int _getline(info_passed *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t b = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	b = read_buf(info, buf, &len);
	if (b == -1 || (b == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * signal_handler - Blocks ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: void.
 */
void signal_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
