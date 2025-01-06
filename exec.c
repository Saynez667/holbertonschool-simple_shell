#include "shell.h"
#include <fcntl.h>

/**
 * handle_redirection - Handles output redirection for commands.
 * @args: Array of command arguments.
 *
 * This function processes the redirection operator (>) and sets up
 * the redirection of standard output to the specified file.
 */
void handle_redirection(char **args)
{
	int i;
	int fd;

	for (i = 0; args[i] != NULL; i++)
	{
		if (strcmp(args[i], ">") == 0)
		{
			if (args[i + 1] == NULL)
			{
				fprintf(stderr, "No file specified for redirection\n");
				return;
			}
			args[i] = NULL;
			fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				return;
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return;
			}
			close(fd);
			break;
		}
	}
}

/**
 * execute_builtin - Executes built-in commands like "env", "exit", or "cd".
 * @args: Array of command arguments.
 *
 * Return: 1 if a built-in command was executed, 0 otherwise
 */
int execute_builtin(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	if (strcmp(args[0], "exit") == 0 && args[1] != NULL)
	{
		return (1);
	}
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		exit(0);
	}
	if (strcmp(args[0], "cd") == 0)
	{
		change_directory(args);
		return (1);
	}
	return (0);
}

/**
 * execute_command - Executes a given command by forking and using execve.
 * @args: Array of command arguments.
 *
 * This function handles the command execution by creating a child
 * process and running the command using execve.
 */
#include "shell.h"
#include <fcntl.h>

void execute_command(char **args)
{
    char *full_path = NULL;
    pid_t pid;

    if (args == NULL || args[0] == NULL)
        return;

    if (execute_builtin(args))
        return;

    // Recherche la commande dans le PATH si ce n'est pas un chemin absolu
    if (strchr(args[0], '/') == NULL)
    {
        full_path = find_command_in_path(args[0]);
        if (full_path == NULL)
        {
            fprintf(stderr, "%s: command not found\n", args[0]);
            return;  // Ne pas faire de fork si la commande n'est pas trouvée
        }
    }
    else
    {
        full_path = args[0];
    }

    // Maintenant que nous avons trouvé la commande, nous pouvons faire un fork
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        // Code du processus enfant
        if (execve(full_path, args, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // Code du processus parent
        wait(NULL);
    }

    if (full_path != args[0])
        free(full_path);
}
