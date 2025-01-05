#include "shell.h"

/**
 * execute - Executes a command
 * @line_input: Line input from the user
 *
 * Return: exit_stat (0 on success or -1 on error)
 */
int execute(char *line_input)
{
    char **args = NULL;
    pid_t pid;
    int status, exit_stat = 0;

    args = tokenize(line_input);
    if (args == NULL)
        return (-1); /* Return -1 if tokenization fails */

    if (args[0][0] == '/')
    {
        /* Handle absolute path execution */
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            free_tokens(args);
            return (-1);
        }
        else if (pid == 0)
        {
            if (execve(args[0], args, environ) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(&status);
            if (WIFEXITED(status))
                exit_stat = WEXITSTATUS(status);
        }
    }
    else
    {
        /* Handle command execution using PATH */
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            free_tokens(args);
            return (-1);
        }
        else if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(&status);
            if (WIFEXITED(status))
                exit_stat = WEXITSTATUS(status);
        }
    }

    free_tokens(args);
    return (exit_stat);
}
