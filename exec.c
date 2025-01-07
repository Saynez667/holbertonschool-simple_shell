#include "shell.h"

/**
 * check_path - Checks if command exists in given path
 * @path: Path to check
 * Return: 1 if exists and executable, 0 if not
 */
int check_path(char *path)
{
	struct stat st;

	if (stat(path, &st) == -1 || !(st.st_mode & S_IXUSR))
		return (0);
	return (1);
}

/**
 * get_command_path - Gets the path for a command
 * @args: Command arguments
 * @program_name: Shell name for errors
 * Return: Path to command or NULL
 */
char *get_command_path(char **args, char *program_name)
{
	char *path = NULL;

	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
	{
		if (!check_path(args[0]))
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
			print_error(program_name, args[0], "not found");
	}
	return (path);
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

	path = get_command_path(args, program_name);
	if (!path)
		return;

	child_pid = fork();
	if (child_pid == -1)
	{
		free(path);
		return;
	}

	if (child_pid == 0)
	{
		execve(path, args, env);
		perror("execve");
		free(path);
		exit(127);
	}
	waitpid(child_pid, &status, 0);
	free(path);
}
