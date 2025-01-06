#include "shell.h"

/**
 * execute_builtin - Execute built-in commands
 * @args: Array of arguments
 *
 * Return: 1 if builtin was executed, 0 otherwise
 */
int execute_builtin(char **args)
{
	if (!args || !args[0])
		return (0);

	if (_strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		exit(0);
	}

	if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	if (_strcmp(args[0], "cd") == 0)
	{
		change_directory(args);
		return (1);
	}

	return (0);
}