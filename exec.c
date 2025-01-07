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
	char *command_path = NULL;
	int status, num_args;
	pid_t child_pid;

	num_args = tokenize_input(input, args);
	if (num_args == 0)
		return;

	if (handle_builtin_commands(args, num_args, input, env) == 1)
		return;

	command_path = get_file_path(args[0]);
	if (!command_path)
	{
		print_error(program_name, args[0], "not found");
		return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		free(command_path);
		return;
	}

	if (child_pid == 0)
	{
		execve(command_path, args, env);
		perror("Error");
		free(command_path);
		exit(127);
	}
	
	wait(&status);
	free(command_path);
}