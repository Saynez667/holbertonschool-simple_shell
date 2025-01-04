#include "shell.h"

/**
 * execute_command - Executes the given command
 * @command: The command to execute
 * @program_name: Name of the shell program (argv[0])
 *
 * Description: This function creates a child process using fork() and
 * executes the given command using execve(). The parent process waits
 * for the child to complete using waitpid(). It handles errors and
 * provides appropriate error messages.
 */
void execute_command(char *command, char *program_name)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror(program_name);
		return;
	}
	else if (pid == 0)
	{
		char *args[] = {command, NULL};

		if (execve(command, args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
