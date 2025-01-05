#include "shell.h"

/**
 * execute - Execute a single command
 * @command: The command to execute
 *
 * Return: 0 on success, -1 on failure
 */
/**
 * execute - execute command path, child process
 * @args: arguments
 * Return: exit status
 */

int execute(char **args)
{
	int id = fork(), status;

	if (id == 0)
	{
		if (execve(args[0], args, environ) == -1)
			perror("Error");
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}

	return (status);
}