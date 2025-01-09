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
 * handle_command_path - Handles command path resolution using stat
 * @args: Array of arguments
 * @program_name: Name of the shell program
 * @env: Environment variables array
 *
 * Return: Command path or NULL
 */
char *handle_command_path(char **args, char *program_name, char **env)
{
	char *cmd_path = NULL;
	struct stat st;

	if (!args || !args[0])
		return (NULL);

	/* If command is empty or too long */
	if (args[0][0] == '\0')
	{
		print_error(program_name, args[0], "not found");
		return (NULL);
	}

	/* If command contains a slash, use it directly */
	if (_strchr(args[0], '/') != NULL)
	{
		if (stat(args[0], &st) == -1)
		{
			print_error(program_name, args[0], "not found");
			return (NULL);
		}
		if (!(st.st_mode & S_IXUSR))
		{
			print_error(program_name, args[0], "Permission denied");
			return (NULL);
		}
		return (_strdup(args[0]));
	}

	/* Search in PATH */
	cmd_path = get_file_path(args[0], env);
	if (!cmd_path)
	{
		print_error(program_name, args[0], "not found");
		return (NULL);
	}

	/* Verify if we have permission to execute */
	if (stat(cmd_path, &st) == 0 && !(st.st_mode & S_IXUSR))
	{
		print_error(program_name, args[0], "Permission denied");
		free(cmd_path);
		return (NULL);
	}

	return (cmd_path);
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
	int status = 0, num_args;
	pid_t child_pid;

	num_args = tokenize_input(input, args);
	if (num_args == 0)
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

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		free(cmd_path);
		free_tokens(args, num_args);
		return (1);
	}

	if (child_pid == 0)
		execute_child(cmd_path, args, env);

	waitpid(child_pid, &status, 0);
	free(cmd_path);
	free_tokens(args, num_args);
	return (WEXITSTATUS(status));
}
