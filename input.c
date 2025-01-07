#include "shell.h"

/**
  * read_input - Reads the input from the users
  *
  * Return: Character variable to the program
  */
char *read_input(void)
{
	char *input_buffer;
	size_t buf_size;
	ssize_t nread;

	input_buffer = NULL;
	buf_size = 0;

	nread = getline(&input_buffer, &buf_size, stdin);

	if (nread == -1)
	{
		free(input_buffer);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		return (NULL);
	}

	/* Remplacer le retour à la ligne par \0 si présent */
	if (input_buffer[nread - 1] == '\n')
		input_buffer[nread - 1] = '\0';

	return (input_buffer);
}
