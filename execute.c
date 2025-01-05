#include "shell.h"

/**
 * execute - execute command path, child process
 * @args: arguments
 * Return: exit status
 */
int execute(char **args)
{
    int id = fork(), status;

    if (id == 0)
    {
        if (execve(args[0], args, environ) == -1)
            perror("Error");
        exit(EXIT_FAILURE);  /* Exit child process on error */
    }
    else if (id < 0)
    {
        perror("Error");  /* Error handling for fork failure */
        return -1;
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
    }
    return (status);
}
