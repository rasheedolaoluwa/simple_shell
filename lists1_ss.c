#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The size of the list.
 */
size_first list_len(const list_str *h)
{
	size_first i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - Converts a linked list to an array of strings.
 * @head: Pointer to the first node of the list.
 *
 * Return: Array of strings representing the list.
 */
char **list_to_strings(list_str *head)
{
	list_str *node = head;
	size_first i = list_len(head), a;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (a = 0; a < i; a++)
				free(strs[a]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a list_str linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The size of the list.
 */
size_first print_list(const list_str *h)
{
	size_first i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * prefix_start - Returns the node whose string starts with a given prefix.
 * @node: Pointer to the list head.
 * @prefix: String prefix to match.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL.
 */
list_str *prefix_start(list_str *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = hay_checker(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_index - Gets the index of a specific node in the list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node in question.
 *
 * Return: Index of the node or -1.
 */
size_second get_index(list_str *head, list_str *node)
{
	size_first i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}