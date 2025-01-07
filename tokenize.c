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

	if (!input || !args)
		return (0);

	/* Créer une copie pour préserver l'original */
	input_copy = _strdup(input);
	if (!input_copy)
		return (0);

	token = strtok(input_copy, " \t\n");
	while (token && count < 9)  /* Réserver un espace pour NULL */
	{
		args[count] = token;
		token = strtok(NULL, " \t\n");
		count++;
	}

	/* S'assurer que le dernier élément est NULL */
	args[count] = NULL;
	return (count);
}
