#include "shell.h"

/**
  * read_input - Reads the input from the users
  *
  * Return: Character variable to the program, NULL if error
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
		return (NULL);  /* Main gèrera la sortie */
	}

	if (nread > 0 && input_buffer[nread - 1] == '\n')
		input_buffer[nread - 1] = '\0';

	return (input_buffer);
}
