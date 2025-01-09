#include "shell.h"

/**
 * tokenize_input - Tokenizes the input string into arguments
 * @input: Input string to tokenize
 * @args: Array to store tokenized arguments
 *
 * Description: Splits input string into tokens, handling spaces and tabs.
 * Ensures proper memory management and bounds checking.
 *
 * Return: Number of tokens processed, or 0 on failure
 */
int tokenize_input(char *input, char *args[])
{
	int count = 0;
	char *token, *input_copy, *trimmed_token;
	const char *delimiters = " \t\n\r";

	if (!input || !args)
		return (0);

	/* Create a copy of input for tokenization */
	input_copy = _strdup(input);
	if (!input_copy)
		return (0);

	/* Get first token */
	token = strtok(input_copy, delimiters);
	while (token && count < 9)
	{
		/* Trim and validate token */
		trimmed_token = trim_token(token);
		if (trimmed_token && *trimmed_token)
		{
			/* Duplicate trimmed token */
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

	/* Ensure array is NULL-terminated */
	args[count] = NULL;
	free(input_copy);
	return (count);
}

/**
 * trim_token - Removes leading and trailing whitespace from a string
 * @str: String to trim
 *
 * Return: Pointer to trimmed string
 */
char *trim_token(char *str)
{
	char *end;

	/* Return NULL if str is NULL */
	if (!str)
		return (NULL);

	/* Skip leading whitespace */
	while (*str && (*str == ' ' || *str == '\t'))
		str++;

	/* If string is empty or only whitespace */
	if (*str == '\0')
		return (str);

	/* Find end of string */
	end = str + _strlen(str) - 1;

	/* Remove trailing whitespace */
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;

	/* Null terminate string after last non-whitespace char */
	*(end + 1) = '\0';

	return (str);
}

/**
 * free_tokens - Frees an array of strings
 * @tokens: Array of strings to free
 * @count: Number of tokens in array
 */
void free_tokens(char **tokens, int count)
{
	int i;

	if (!tokens)
		return;

	for (i = 0; i < count; i++)
	{
		if (tokens[i])
		{
			free(tokens[i]);
			tokens[i] = NULL;
		}
	}
}
