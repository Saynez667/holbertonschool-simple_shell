#include "shell.h"

/**
 * execute - Execute a single command
 * @command: The command to execute
 */
void execute(char *command)
{
    pid_t pid;
    int status;
    char *args[2];

    args[0] = command;
    args[1] = NULL;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
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

