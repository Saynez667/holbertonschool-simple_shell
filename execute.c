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
        perror("./hsh");
        return;
    }
    if (pid == 0)
    {
        if (execve(command, args, environ) == -1)
        {
            write(STDERR_FILENO, "./hsh: 1: ", 10);
            write(STDERR_FILENO, command, strlen(command));
            write(STDERR_FILENO, ": not found\n", 12);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }
}

