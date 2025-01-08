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
 * is_executable - Checks if file exists and is executable
 * @path: Path to check
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(char *path)
{
	struct stat st;

	if (!path)
		return (0);

	if (stat(path, &st) == 0)
	{
		if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
			return (1);
		errno = EACCES;
		return (0);
	}

	return (0);
}

/**
 * handle_command_path - Handles command path resolution
 * @args: Array of arguments
 * @program_name: Name of the shell program
 *
 * Return: Command path or NULL
 */
char *handle_command_path(char **args, char *program_name)
{
	char *cmd_path = NULL;

	if (!args || !args[0])
		return (NULL);

	if (_strchr(args[0], '/'))
	{
		if (is_executable(args[0]))
			cmd_path = _strdup(args[0]);
	}
	else
		cmd_path = get_file_path(args[0]);

	if (!cmd_path)
	{
		print_error(program_name, args[0],
				errno == EACCES ? "Permission denied" : "not found");
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

	cmd_path = handle_command_path(args, program_name);
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
