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

	/* Read input using custom_getline */
	nread = custom_getline(&input_buffer, &buf_size, STDIN_FILENO);

	if (nread == -1)
	{
		free(input_buffer);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		return (NULL);
	}

	/* Remove trailing newline if present */
	if (nread > 0 && input_buffer[nread - 1] == '\n')
		input_buffer[nread - 1] = '\0';

	/* Check for empty input */
	if (input_buffer[0] == '\0')
	{
		free(input_buffer);
		return (NULL);
	}

	return (input_buffer);
}
