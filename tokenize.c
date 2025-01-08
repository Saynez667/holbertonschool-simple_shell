#include "shell.h"

/**
 * free_tokens - Frees allocated tokens
 * @args: Array of token strings
 * @count: Number of tokens to free
 */
void free_tokens(char **args, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		free(args[i]);
		args[i] = NULL;
	}
}

/**
 * trim_token - Removes leading and trailing spaces from token
 * @token: Token to trim
 *
 * Return: Trimmed token
 */
char *trim_token(char *token)
{
	char *end;

	if (!token)
		return (NULL);

	/* Skip leading spaces */
	while (*token == ' ' || *token == '\t')
		token++;

	/* If string is all spaces */
	if (*token == '\0')
		return (token);

	/* Find end of string */
	end = token + _strlen(token) - 1;

	/* Trim trailing spaces */
	while (end > token && (*end == ' ' || *end == '\t'))
		end--;

	/* Null terminate the trimmed string */
	*(end + 1) = '\0';

	return (token);
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
	char *token, *input_copy, *trimmed_token;
	const char *delimiters = " \t\n\r";

	if (!input || !args)
		return (0);

	input_copy = _strdup(input);
	if (!input_copy)
		return (0);

	token = strtok(input_copy, delimiters);
	while (token && count < 9)
	{
		trimmed_token = trim_token(token);
		if (trimmed_token && *trimmed_token)
		{
			args[count] = _strdup(trimmed_token);
			if (!args[count])
			{
				free_tokens(args, count);
				free(input_copy);
				return (0);
			}
			count++;
		}
		token = strtok(NULL, delimiters);
	}

	args[count] = NULL;
	free(input_copy);
	return (count);
}
