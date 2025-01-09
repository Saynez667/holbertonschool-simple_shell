#include "shell.h"

/**
 * print_env - Prints the environment variables
 * @env: Array of environment variables
 *
 * Description: Iterates through environment variables and prints
 * each one followed by a newline
 */
void print_env(char **env)
{
	int i;
	char *env_var;

	if (!env)
		return;

	for (i = 0; env[i]; i++)
	{
		env_var = env[i];
		if (env_var)
		{
			write(STDOUT_FILENO, env_var, _strlen(env_var));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}

#include "shell.h"

/**
 * handle_setenv - Handle the setenv builtin command
 * @args: Command arguments (args[1] = variable, args[2] = value)
 * @program_name: Name of the shell program
 *
 * Return: 0 on success, 1 on failure
 */
int handle_setenv(char **args, char *program_name)
{
	if (!args[1] || !args[2])
	{
		print_error(program_name, "setenv", "Invalid number of arguments");
		return (1);
	}

	/* Check for invalid variable name */
	if (strchr(args[1], '='))
	{
		print_error(program_name, "setenv", "Invalid variable name");
		return (1);
	}

	/* Try to set the environment variable */
	if (setenv(args[1], args[2], 1) == -1)
	{
		print_error(program_name, "setenv", "Failed to set environment variable");
		return (1);
	}

	return (0);
}

/**
 * handle_unsetenv - Handle the unsetenv builtin command
 * @args: Command arguments (args[1] = variable to unset)
 * @program_name: Name of the shell program
 *
 * Return: 0 on success, 1 on failure
 */
int handle_unsetenv(char **args, char *program_name)
{
	if (!args[1])
	{
		print_error(program_name, "unsetenv", "Invalid number of arguments");
		return (1);
	}

	/* Check if the variable exists */
	if (!getenv(args[1]))
	{
		print_error(program_name, "unsetenv", "Variable not found");
		return (1);
	}

	/* Try to unset the environment variable */
	if (unsetenv(args[1]) == -1)
	{
		print_error(program_name,
		"unsetenv", "Failed to unset environment variable");
		return (1);
	}

	return (0);
}
