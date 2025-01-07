#include "shell.h"

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

	/* Skip leading whitespace */
	while (*input && (*input == ' ' || *input == '\t' || *input == '\n'))
		input++;

	if (*input == '\0')
		return (0);

	input_copy = _strdup(input);
	if (!input_copy)
		return (0);

	token = strtok(input_copy, delimiters);
	while (token && count < 9)
	{
		args[count] = token;
		count++;
		token = strtok(NULL, delimiters);
	}

	args[count] = NULL;

	if (count == 0)
	{
		free(input_copy);
		return (0);
	}

	return (count);
}
