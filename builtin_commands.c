#include "shell.h"

/**
 * execute_builtin - Execute built-in shell commands
 * @args: Array of command arguments
 * Description: This function handles the execution of built-in shell commands.
 * It supports three commands: 'cd', 'exit', and 'env'.
 * 'cd': Changes the current directory. Prints an error if no argument
 * is provided or if the directory change fails.
 * 'exit': Signals the shell to terminate.
 * 'env': Prints all environment variables.
 * 
 * Return: 0 if the command is a built-in and was executed, -1 if the command is 'exit',
 * 1 if the command is not a built-in
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
