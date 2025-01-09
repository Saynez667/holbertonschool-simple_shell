#include "shell.h"

/**
 * execute_child - Handles the child process execution
 * @cmd_path: Path to the command to execute
 * @args: Array of arguments
 * @env: Environment variables
 */
void execute_child(char *cmd_path, char **args, char **env)
{
	if (execve(cmd_path, args, env) == -1)
	{
		perror("Error");
		free(cmd_path);
		free_tokens(args, get_token_count(args));
		exit(127);
	}
}

/**
 * get_token_count - Count number of tokens
 * @args: Array of tokens
 *
 * Return: Number of tokens
 */
int get_token_count(char **args)
{
	int count = 0;

	if (!args)
		return (0);

	while (args[count])
		count++;

	return (count);
}

/**
 * prepare_command - Prepares command for execution
 * @input: Input string
 * @args: Array to store arguments
 *
 * Return: Number of arguments, or -1 on empty input
 */
int prepare_command(char *input, char **args)
{
	char *trimmed_input = trim_spaces(input);
	int num_args;

	if (!trimmed_input || !*trimmed_input)
		return (-1);

	num_args = tokenize_input(trimmed_input, args);
	if (num_args == 0)
		return (-1);

	return (num_args);
}

/**
 * handle_fork - Handles the fork and execution process
 * @cmd_path: Command path
 * @args: Command arguments
 * @env: Environment variables
 *
 * Return: Exit status of child process
 */
int handle_fork(char *cmd_path, char **args, char **env)
{
	pid_t child_pid;
	int status = 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}

	if (child_pid == 0)
		execute_child(cmd_path, args, env);

	waitpid(child_pid, &status, 0);
	return (WEXITSTATUS(status));
}

/**
 * execute_command - Executes the input from the buffer
 * @input: The argument from the buffer
 * @argv: Array of argument
 * @env: Environment variables
 * @program_name: Name of the shell program
 *
 * Return: Exit status of the command
 */
int execute_command(char *input, char *argv[] __attribute__((unused)),
		char **env, char *program_name)
{
	char *args[10];
	char *cmd_path = NULL;
	int status, num_args;

	num_args = prepare_command(input, args);
	if (num_args == -1)
		return (0);

	if (handle_builtin_commands(args, num_args, input, env) == 1)
	{
		free_tokens(args, num_args);
		return (0);
	}

	cmd_path = handle_command_path(args, program_name, env);
	if (!cmd_path)
	{
		free_tokens(args, num_args);
		return (127);
	}

	status = handle_fork(cmd_path, args, env);
	free(cmd_path);
	free_tokens(args, num_args);
	return (status);
}
