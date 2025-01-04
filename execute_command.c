#include "shell.h"

/**
 * execute_command - Execute a command
 * @command: The command to execute
 *
 * Description: This function forks a new process and uses execve
 * to run the specified command. It waits for the child process
 * to complete before returning.
 *
 * Return: 0 on success, 1 on failure
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = command;
	args[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(command, args, environ) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		/* Error forking */
		perror("fork");
		return (1);
	}
	else
	{
		/* Parent process */
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}
	}

	return (0);
}