#include "shell.h"

/**
 * execute_command - Executes the given command
 * @command: The command to execute
 *
 * Description: This function creates a child process using fork() and
 * executes the given command using execve(). The parent process waits
 * for the child to complete using waitpid().
 */
void execute_command(char *command)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1)
    {
        perror("Error:");
        return;
    }
    else if (pid == 0)
    {
        char *args[] = {command, NULL};

        if (execve(command, args, environ) == -1)
        {
            printf("%s: No such file or directory\n", command);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }
}
