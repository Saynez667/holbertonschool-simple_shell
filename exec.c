#include "shell.h"

/**
 * execute_command - Executes the input from the buffer
 * @input: The argument from the buffer
 * @argv: Array of argument
 * @env: Environment variables
 * @program_name: Name of the shell program
 */
void execute_command(char *input, char *argv[] __attribute__((unused)),
		char **env, char *program_name)
{
	char *args[10];
	char *cmd_path = NULL;
	int status, num_args;
	pid_t child_pid;

	num_args = tokenize_input(input, args);
	if (num_args == 0)
		return;

	/* Check for built-in commands first */
	if (handle_builtin_commands(args, num_args, input, env) == 1)
		return;

	/* Handle absolute or relative paths */
	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
	{
		if (access(args[0], F_OK) == -1)
		{
			print_error(program_name, args[0], "not found");
			return;
		}
		cmd_path = _strdup(args[0]);
	}
	else
	{
		/* Search in PATH */
		cmd_path = get_file_path(args[0]);
	}

	/* Only fork if command exists */
	if (cmd_path != NULL)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			free(cmd_path);
			return;
		}

		if (child_pid == 0)
		{
			if (execve(cmd_path, args, env) == -1)
			{
				perror("Error");
				free(cmd_path);
				exit(127);
			}
		}
		else
		{
			wait(&status);
		}
		free(cmd_path);
	}
	else
	{
		print_error(program_name, args[0], "not found");
	}
}