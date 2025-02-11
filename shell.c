#include "shell.h"

/**
 * main - Simple shell main program
 * @argc: Argument count
 * @argv: Array of arguments
 * @env: Environment variables
 *
 * Return: Exit status
 */
int main(int argc __attribute__((unused)), char *argv[], char **env)
{
	char *input_buffer = NULL;
	int status = 0;
	int interactive;

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			print_prompt();

		input_buffer = read_input();
		if (!input_buffer)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Skip empty lines and continue */
		if (input_buffer[0] == '\0' || input_buffer[0] == '\n')
		{
			free(input_buffer);
			input_buffer = NULL;
			continue;
		}

		status = execute_command(input_buffer, argv, env, argv[0]);
		free(input_buffer);
		input_buffer = NULL;

		if (status == -1)  /* Handle exit command */
			break;
	}

	return (status);
}
