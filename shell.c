#include "shell.h"

/**
  * main - Simple shell main program
  * @argc: Argument count
  * @argv: Array of arguments
  * @env: Environment variables
  *
  * Return: Last status
  */
int main(int argc __attribute__((unused)), char *argv[], char **env)
{
	char *input_buffer = NULL;
	int status = 0;

	while (1)
	{
		print_prompt();
		input_buffer = read_input();

		if (!input_buffer)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}

		status = execute_command(input_buffer, argv, env, argv[0]);
		free(input_buffer);
		input_buffer = NULL;
	}

	return (status);
}
