#include "shell.h"

/**
 * execute_pipeline - Execute a pipeline of commands
 * @input: The input string containing the pipeline
 *
 * Return: 0 on success, 1 on failure
 */
int execute_pipeline(char *input)
{
	int i, j, pipe_count = 0;
	int pipe_fds[MAX_PIPES][2];
	char *commands[MAX_PIPES + 1];
	pid_t pid;

	/* Split the input into separate commands */
	commands[0] = strtok(input, "|");
	while ((commands[++pipe_count] = strtok(NULL, "|")) != NULL &&
			pipe_count < MAX_PIPES)
		;

	/* Create pipes */
	for (i = 0; i < pipe_count - 1; i++)
	{
		if (pipe(pipe_fds[i]) < 0)
		{
			perror("pipe");
			return (1);
		}
	}

	/* Execute commands */
	for (i = 0; i < pipe_count; i++)
	{
		char **args = parse_command(commands[i]);

		pid = fork();
		if (pid == 0)
		{
			/* Child process */
			if (i > 0)
			{
				/* Redirect input from previous pipe */
				dup2(pipe_fds[i - 1][0], STDIN_FILENO);
			}
			if (i < pipe_count - 1)
			{
				/* Redirect output to next pipe */
				dup2(pipe_fds[i][1], STDOUT_FILENO);
			}

			/* Close all pipe file descriptors */
			for (j = 0; j < pipe_count - 1; j++)
			{
				close(pipe_fds[j][0]);
				close(pipe_fds[j][1]);
			}

			handle_redirection(args);

			char *cmd_path = find_executable(args[0]);
			if (cmd_path == NULL)
			{
				fprintf(stderr, "%s: command not found\n", args[0]);
				exit(EXIT_FAILURE);
			}

			execve(cmd_path, args, environ);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("fork");
			return (1);
		}

		free(args);
	}

	/* Close all pipe file descriptors in the parent */
	for (i = 0; i < pipe_count - 1; i++)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
	}

	/* Wait for all child processes */
	for (i = 0; i < pipe_count; i++)
	{
		wait(NULL);
	}

	return (0);
}