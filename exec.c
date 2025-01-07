#include "shell.h"
/**
 * execute_child - Handles the child process execution
 * @cmd_path: Path to the command to execute
 * @args: Array of arguments
 * @env: Environment variables
 * Return: void
 */
void execute_child(char *cmd_path, char *args[], char **env)
{
	if (execve(cmd_path, args, env) == -1)
	{
		perror("Error");
		free(cmd_path);
		exit(127);
	}
}

/**
 * handle_command_path - Handles command path resolution
 * @args: Array of arguments
 * @program_name: Name of the shell program
 * Return: Command path or NULL
 */
char *handle_command_path(char *args[], char *program_name)
{
	char *cmd_path = NULL;

	if (!args[0])
		return (NULL);

	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
	{
		if (access(args[0], X_OK) == -1)
		{
			print_error(program_name, args[0], "not found");
			return (NULL);
		}
		cmd_path = _strdup(args[0]);
	}
	else
		cmd_path = get_file_path(args[0]);

	return (cmd_path);
}

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

	if (handle_builtin_commands(args, num_args, input, env) == 1)
		return;

	cmd_path = handle_command_path(args, program_name);
	if (cmd_path == NULL)
	{
		print_error(program_name, args[0], "not found");
		return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		free(cmd_path);
		return;
	}

	if (child_pid == 0)
		execute_child(cmd_path, args, env);
	else
		wait(&status);

	free(cmd_path);
}
