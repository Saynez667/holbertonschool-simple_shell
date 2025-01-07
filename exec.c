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
	char *path = NULL;
	int status, num_args;
	pid_t child_pid;
	struct stat st;

	num_args = tokenize_input(input, args);
	if (num_args == 0)
		return;

	if (handle_builtin_commands(args, num_args, input, env) == 1)
		return;

	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
	{
		if (stat(args[0], &st) == -1 || !(st.st_mode & S_IXUSR))
		{
			print_error(program_name, args[0], "not found");
			return;
		}
		path = _strdup(args[0]);
	}
	else
	{
		path = get_file_path(args[0]);
		if (!path)
		{
			print_error(program_name, args[0], "not found");
			return;
		}
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(path);
		return;
	}

	if (child_pid == 0)
	{
		if (execve(path, args, env) == -1)
		{
			perror("execve");
			free(path);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
	free(path);
}