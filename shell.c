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

	while (1)
	{
		print_prompt(); /* print_prompt gérera isatty() */
		input_buffer = read_input();

		if (!input_buffer) /* EOF (Ctrl+D) détecté */
		{
			return (status);
		}

		status = execute_command(input_buffer, argv, env, argv[0]);
		free(input_buffer);
		input_buffer = NULL;
	}
}
