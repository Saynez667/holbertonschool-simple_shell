#include "shell.h"

/**
 * execute_command - Execute command with arguments
 * @args: Command and arguments
 *
 * Return: Exit status
 */
int execute_command(char **args)
{
	char *cmd;
	pid_t child_pid;
	int status;

	if (!args || !args[0])
		return (1);

	/* Check builtins first */
	if (execute_builtin(args))
		return (0);

	/* Then check if command exists in PATH */
	cmd = find_command_in_path(args[0]);
	if (!cmd)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (127);
	}

	/* Only fork if command exists */
	child_pid = fork();
	if (child_pid == -1)
	{
		free(cmd);
		return (1);
	}

	if (child_pid == 0)
	{
		execve(cmd, args, environ);
		perror("execve");
		free(cmd);
		exit(126);
	}
	else
	{
		wait(&status);
		free(cmd);
		return (WEXITSTATUS(status));
	}
}