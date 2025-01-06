#include "shell.h"

/**
 * execute_command - Execute a command with arguments
 * @args: Command and arguments
 * Return: Exit status
 */
int execute_command(char **args)
{
	char *cmd_path;
	pid_t pid;
	int status = 0;

	if (!args || !args[0])
		return (1);

	if (execute_builtin(args))
		return (0);

	cmd_path = find_command_in_path(args[0]);
	if (!cmd_path)
	{
		_print_error(args[0]);
		_print_error(": command not found\n");
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve");
			free(cmd_path);
			_exit(126);
		}
	}

	waitpid(pid, &status, 0);
	free(cmd_path);
	return (WEXITSTATUS(status));
}

/**
 * execute_builtin - Execute built-in commands
 * @args: Command arguments
 * Return: 1 if builtin executed, 0 otherwise
 */
int execute_builtin(char **args)
{
	if (!args || !args[0])
		return (0);

	if (_strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		exit(_atoi(args[1] ? args[1] : "0"));
	}

	if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	if (_strcmp(args[0], "cd") == 0)
	{
		change_directory(args);
		return (1);
	}

	return (0);
}