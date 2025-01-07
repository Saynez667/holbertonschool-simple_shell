#include "shell.h"

/**
 * handle_builtin_commands - Handle all the built in commands
 * @args: Arguments to the built in commands
 * @num_args: Number of arguments
 * @input: The input command
 * @env: The environment variables
 *
 * Return: 1 if builtin command was executed, 0 otherwise
 */
int handle_builtin_commands(char **args, int num_args, char *input, char **env)
{
	if (!args || !args[0])
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		return (shell_exit(args, input));
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		handle_cd(args, num_args);
		return (1);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_env(env);
		return (1);
	}

	return (0);
}
