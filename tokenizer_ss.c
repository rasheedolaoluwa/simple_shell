#include "shell.h"

/**
 * strtow - Splits a string into words, ignoring repeated delimiters
 * @str: The input string to be split
 * @d: String containing delimiters used for splitting
 * Return: Pointer to an array of strings (words), or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, word_index, letter_count, num_words = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) &&
			(is_delim(str[i + 1], d) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, word_index = 0; word_index < num_words; word_index++)
	{
		while (is_delim(str[i], d))
			i++;
		letter_count = 0;
		while (!is_delim(str[i + letter_count], d) && str[i + letter_count])
			letter_count++;
		words[word_index] = malloc((letter_count + 1) * sizeof(char));
		if (!words[word_index])
		{
			for (int j = 0; j < word_index; j++)
				free(words[j]);
			free(words);
			return (NULL);
		}
		for (int k = 0; k < letter_count; k++)
			words[word_index][k] = str[i++];
		words[word_index][letter_count] = '\0';
	}
	words[word_index] = NULL;
	return (words);
}

/**
 * strtow2 - Splits a string into words using a single character delimiter
 * @str: The input string to be split
 * @d: Single character used to split the string
 * Return: Pointer to an array of strings (words), or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, word_index, letter_count, num_words = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, word_index = 0; word_index < num_words; word_index++)
	{
		while (str[i] == d && str[i] != '\0')
			i++;
		letter_count = 0;
		while (str[i + letter_count] != d && str[i + letter_count] &&
			       str[i + letter_count] != d)
			letter_count++;
		words[word_index] = malloc((letter_count + 1) * sizeof(char));
		if (!words[word_index])
		{
			for (int j = 0; j < word_index; j++)
				free(words[j]);
			free(words);
			return (NULL);
		}
		for (int k = 0; k < letter_count; k++)
			words[word_index][k] = str[i++];
		words[word_index][letter_count] = '\0';
	}
	words[word_index] = NULL;
	return (words);
}
