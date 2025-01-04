#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Description: This function implements the main loop for a simple shell.
 * It reads user commands, processes them, and executes them until the user
 * chooses to exit or an EOF is encountered. It handles both interactive
 * and non-interactive modes.
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char **argv)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		nchars_read = getline(&lineptr, &n, stdin);

		if (nchars_read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		lineptr[strcspn(lineptr, "\n")] = '\0';

		if (strlen(lineptr) == 0)
			continue;
            
            execute_command(lineptr, argv[0]);
	}

	free(lineptr);
	return (0);
}
