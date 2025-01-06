#include "shell.h"

/**
 * read_input - Reads user input from stdin
 *
 * Return: Pointer to input string, NULL on EOF or error
 */
char *read_input(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;
	int i;

	chars_read = getline(&line, &bufsize, stdin);
	if (chars_read == -1)
	{
		free(line);
		if (feof(stdin))
			return (NULL);
		perror("getline");
		return (NULL);
	}

	/* Remove trailing newline */
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}
	}

	return (line);
}