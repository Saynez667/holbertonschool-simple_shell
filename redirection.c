#include "shell.h"

/**
 * handle_redirection - Handle input/output redirection
 * @args: Array of command arguments
 */
void handle_redirection(char **args)
{
	int i, in_fd = -1, out_fd = -1;

	for (i = 0; args[i] != NULL; i++)
	{
		if (strcmp(args[i], "<") == 0)
		{
			if (args[i + 1] == NULL)
			{
				fprintf(stderr, "Syntax error near unexpected token `<'\n");
				return;
			}
			in_fd = open(args[i + 1], O_RDONLY);
			if (in_fd == -1)
			{
				perror("open");
				return;
			}
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
			args[i] = NULL;
			i++;
		}
		else if (strcmp(args[i], ">") == 0)
		{
			if (args[i + 1] == NULL)
			{
				fprintf(stderr, "Syntax error near unexpected token `>'\n");
				return;
			}
			out_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out_fd == -1)
			{
				perror("open");
				return;
			}
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
			args[i] = NULL;
			i++;
		}
		else if (strcmp(args[i], ">>") == 0)
		{
			if (args[i + 1] == NULL)
			{
				fprintf(stderr, "Syntax error near unexpected token `>>'\n");
				return;
			}
			out_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (out_fd == -1)
			{
				perror("open");
				return;
			}
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
			args[i] = NULL;
			i++;
		}
	}
}