#include "shell.h"

/**
 * get_token_count - Count number of tokens in array
 * @args: Array of tokens
 *
 * Return: Number of tokens
 */
int get_token_count(char **args)
{
	int count = 0;

	if (!args)
		return (0);

	while (args[count])
		count++;

	return (count);
}

/**
 * free_tokens - Frees allocated tokens
 * @args: Array of token strings
 * @count: Number of tokens to free
 */
void free_tokens(char **args, int count)
{
	int i;

	if (!args)
		return;

	for (i = 0; i < count; i++)
	{
		if (args[i])
			free(args[i]);
	}
}

/**
 * trim_input - Removes leading and trailing whitespace
 * @str: String to trim
 *
 * Return: Pointer to first non-whitespace char
 */
char *trim_input(char *str)
{
	char *end;

	while (*str && (*str == ' ' || *str == '\t'))
		str++;

	if (*str == 0)
		return (str);

	end = str + _strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	end[1] = '\0';
	return (str);
}

/**
 * tokenize_input - Tokenizes the input strings
 * @input: Argument input
 * @args: The array of strings
 *
 * Return: Number of the items tokenized
 */
int tokenize_input(char *input, char *args[])
{
	int count = 0;
	char *token, *input_copy, *trimmed;
	const char *delimiters = " \t\n";

	if (!input || !args)
		return (0);

	trimmed = trim_input(input);
	if (!*trimmed)
		return (0);

	input_copy = _strdup(trimmed);
	if (!input_copy)
		return (0);

	token = strtok(input_copy, delimiters);
	while (token && count < 9)
	{
		args[count] = _strdup(token);
		if (!args[count])
		{
			free_tokens(args, count);
			free(input_copy);
			return (0);
		}
		count++;
		token = strtok(NULL, delimiters);
	}

	args[count] = NULL;
	free(input_copy);
	return (count);
}
