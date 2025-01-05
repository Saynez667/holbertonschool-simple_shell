#include "shell.h"

/**
 * execute - Execute a single command
 * @command: The command to execute
 */
void execute(char *command)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        if (execve(command, (char *[]){command, NULL}, environ) == -1)
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
