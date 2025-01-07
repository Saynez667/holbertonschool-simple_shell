#include "shell.h"

/**
  * execute_command - Executes the input from the buffer
  * @input: The argument from the buffer
  * @argv: Array of argument
  * @env: Environment variables
  */
void execute_command(char *input, char *argv[] __attribute__((unused)), char **env)
{
	char *args[10];
	char *path;
	int status, num_args;
	pid_t child_pid;

	num_args = tokenize_input(input, args);

	if (num_args == 0)
		return;
	if (handle_builtin_commands(args, num_args, input, env) == 1)
		return;
	path = get_file_path(args[0]);

	if (!path)
	{
    fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
    return;
	}
	
	if (access(path, X_OK) == -1)
    {
        fprintf(stderr, "./hsh: 1: %s: Permission denied\n", args[0]);
        free(path);
        return;
    }

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: Failed to create");
		free(input);
		exit(1);
	}

	if (child_pid == 0)
	{
		if (execve(path, args, env) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			free(path);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
        status = WEXITSTATUS(status);
	}

	free(path);
}