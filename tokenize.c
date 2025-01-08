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
		{
			free(args[i]);
			args[i] = NULL;
		}
	}
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
	char *token, *input_copy;
	const char *delimiters = " \t\n\r";

	if (!input || !args)
		return (0);

	input_copy = _strdup(input);
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
