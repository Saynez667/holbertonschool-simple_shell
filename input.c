#include "shell.h"
/**
 * read_input - Reads and processes input from standard input
 *
 * Description: Reads a line of input, handles empty lines and whitespace.
 * Performs proper memory management and error checking.
 *
 * Return: Pointer to input string, or NULL if empty/error
 */
char *read_input(void)
{
	char *input_buffer = NULL;
	size_t buf_size = 0;
	ssize_t nread;
	int i, only_spaces = 1;

	/* Read input using getline */
	nread = getline(&input_buffer, &buf_size, stdin);

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

	/* Check if input contains only spaces/tabs */
	for (i = 0; input_buffer[i] != '\0'; i++)
	{
		if (input_buffer[i] != ' ' && input_buffer[i] != '\t')
		{
			only_spaces = 0;
			break;
		}
	}

	/* Free and return NULL if input is empty or only whitespace */
	if (only_spaces)
	{
		free(input_buffer);
		return (NULL);
	}

	return (input_buffer);
}
