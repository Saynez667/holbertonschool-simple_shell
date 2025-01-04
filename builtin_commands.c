#include "shell.h"

/**
 * execute_builtin - Execute built-in shell commands
 * @args: Array of command arguments
 * 
 * Return: 0 if the command is a built-in, 1 otherwise
 */
int execute_builtin(char **args)
{
    char **env;

    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "cd: missing argument\n");
        }
        else
        {
            if (chdir(args[1]) != 0)
            {
                perror("chdir");
            }
        }
        return (0);
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        return (-1);
    }
    else if (strcmp(args[0], "env") == 0)
    {
        for (env = environ; *env != NULL; env++)
        {
            printf("%s\n", *env);
        }
        return (0);
    }
    return (1);
}