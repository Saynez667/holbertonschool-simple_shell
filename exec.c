#include "shell.h"

/**
 * check_command_path - Check if command exists and get its path
 * @args: Command and arguments
 * @program_name: Name of shell program for error messages
 * Return: Path to command if found, NULL otherwise
 */
char *check_command_path(char **args, char *program_name)
{
	char *path = NULL;

	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
	{
		if (access(args[0], F_OK | X_OK) == -1)
		{
			print_error(program_name, args[0], "not found");
			return (NULL);
		}
		path = _strdup(args[0]);
	}
	else
	{
		path = get_file_path(args[0]);
		if (!path)
		{
			print_error(program_name, args[0], "not found");
			return (NULL);
		}
	}
	return (path);
}

/**
 * execute_child - Execute command in child process
 * @path: Path to executable
 * @args: Command arguments
 * @env: Environment variables
 */
void execute_child(char *path, char **args, char **env)
{
	if (execve(path, args, env) == -1)
	{
		perror("Error");
		free(path);
		exit(127);
	}
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
	char *path = NULL;
	int status, num_args;
	pid_t child_pid;

	num_args = tokenize_input(input, args);
	if (num_args == 0)
		return;

	if (handle_builtin_commands(args, num_args, input, env) == 1)
		return;

	path = check_command_path(args, program_name);
	if (!path)
		return;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		free(path);
		return;
	}

	if (child_pid == 0)
		execute_child(path, args, env);
	else
		waitpid(child_pid, &status, 0);

	free(path);
}
