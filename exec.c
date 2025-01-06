#include "shell.h"
#include <fcntl.h>

/**
 * handle_redirection - Handles output redirection for commands
 * @args: Array of command arguments
 *
 * Return: void
 */
void handle_redirection(char **args)
{
	int i, fd;

	for (i = 0; args[i] != NULL; i++)
	{
		if (_strcmp(args[i], ">") == 0)
		{
			if (args[i + 1] == NULL)
			{
				_print_error("No file specified for redirection\n");
				return;
			}
			args[i] = NULL;
			fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				return;
			}
			if (close(STDOUT_FILENO) == -1)
			{
				perror("close");
				close(fd);
				return;
			}
			if (open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644) != STDOUT_FILENO)
			{
				_print_error("Failed to redirect output\n");
				close(fd);
				return;
			}
			close(fd);
			break;
		}
	}
}

/**
 * execute_builtin - Executes built-in shell commands
 * @args: Array of command arguments
 *
 * Return: 1 if builtin was executed, 0 otherwise
 */
int execute_builtin(char **args)
{
	int status;

	if (!args || !args[0])
		return (0);

	if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	if (_strcmp(args[0], "exit") == 0)
	{
		status = args[1] ? _atoi(args[1]) : 0;
		free_args(args);
		exit(status);
	}
	if (_strcmp(args[0], "cd") == 0)
	{
		change_directory(args);
		return (1);
	}
	return (0);
}

/**
 * execute_command - Executes a command with arguments
 * @args: Array of command arguments
 *
 * Return: void
 */
void execute_command(char **args)
{
	char *full_path = NULL;
	pid_t pid;
	int status;

	if (!args || !args[0])
		return;

	if (execute_builtin(args))
		return;

	if (_strchr(args[0], '/') == NULL)
	{
		full_path = find_command_in_path(args[0]);
		if (!full_path)
		{
			_print_error(args[0]);
			_print_error(": command not found\n");
			return;
		}
	}
	else
		full_path = _strdup(args[0]);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		return;
	}
	if (pid == 0)
	{
		handle_redirection(args);
		if (execve(full_path, args, environ) == -1)
		{
			perror("execve");
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(full_path);
	}
}