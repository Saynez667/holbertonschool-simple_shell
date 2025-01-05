#include "shell.h"

/**
 * main - Entry point
 *
 * Return: 0 (On success) or -1 (on error)
 */

int main(void)
{
	char *line_input = NULL;
	int ex = 0, r;
	size_t bufsize = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("simpleshell$ ");

		signal(SIGINT, signal_handler);

		r = getline(&line_input, &bufsize, stdin);
		if (r == -1)
		{
			if (feof(stdin))
				printf("\n");
			break;
		}

		if (strcmp(line_input, "exit\n") == 0)
			break;

		if (strcmp(line_input, "env\n") == 0)
		{
			print_env();
			continue;
		}

		ex = execute(line_input);
		if (ex == -1)
			perror("Execution error");
	}

	free(line_input);
	return (ex);
}