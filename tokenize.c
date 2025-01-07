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

	count = 0;
	token = strtok(input, " \t\n");

	while (token)
	{
		args[count] = token;
		token = strtok(NULL, " \t\n");
		count++;
	}

	args[count] = NULL;
	return (count);
}