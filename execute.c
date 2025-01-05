#include "shell.h"

/**
 * execute - Execute a single command
 * @command: The command to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute(char *command)
{
    pid_t pid;
    int status;
    char *argv[2];

    argv[0] = command;
    argv[1] = NULL;

    pid = fork();
    if (pid == -1)
    {
        perror("./hsh");
        return (-1);
    }
    if (pid == 0)
    {
        if (execve(command, argv, environ) == -1)
        {
            return (-1);
        }
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            return (-1);
    }
    return (0);
}
