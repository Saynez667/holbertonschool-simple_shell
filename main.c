#include "shell.h"
#include <signal.h>

/**
 * main - Entry point for shell program
 * Return: 0 on success
 */
int main(void)
{
	char *command = NULL;
	char **args = NULL;
	int status = 0;

	signal(SIGINT, handle_signal);

	while (1)
	{
		prompt();
		command = read_input();

		if (!command)
			break;

		if (command[0] == '\0' || strcmp(command, "\n") == 0)
		{
			free(command);
			continue;
		}

		args = parse_command(command);
		if (!args)
		{
			free(command);
			continue;
		}

		if (args[0])
			execute_command(args);

		free(command);
		free_args(args);
	}

	return (status);
}