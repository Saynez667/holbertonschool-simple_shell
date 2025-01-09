#include "shell.h"

/**
 * read_input - Reads the input from the users
 *
 * Return: Pointer to input string or NULL if EOF or error
 */
char *read_input(void)
{
	char *input_buffer = NULL;
	size_t buf_size = 0;
	ssize_t nread;

	nread = getline(&input_buffer, &buf_size, stdin);
	if (nread == -1)
	{
		free(input_buffer);
		return (NULL);
	}

	return (input_buffer);
}
