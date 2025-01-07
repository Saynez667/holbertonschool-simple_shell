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
	char *token;

	if (!input || !args)
		return (0);

	/* Skip leading whitespace */
	while (*input == ' ' || *input == '\t' || *input == '\n')
		input++;

	if (*input == '\0')
		return (0);

	token = strtok(input, " \t\n");
	while (token)
	{
		if (count >= 9)  /* Garde une place pour le NULL final */
			break;
		args[count] = token;
		token = strtok(NULL, " \t\n");
		count++;
	}

	args[count] = NULL;
	return (count);
}
