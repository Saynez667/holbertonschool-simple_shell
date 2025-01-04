#include "shell.h"

/**
 * execute_input - Execute the user input
 * @input: The user input string
 * 
 * Return: 0 on success, -1 on exit command
 */
int execute_input(char *input)
{
    char **args;
    int status;

    if (strchr(input, '|'))
    {
        return execute_pipeline(input);
    }
    else
    {
        char **args = parse_command(input);
        int status;

        if (args[0] == NULL)
        {
            free(args);
            return (0);
        }

        handle_redirection(args);

        if (execute_builtin(args) == 0)
        {
            free(args);
            return (0);
        }

        status = execute_external(args);
        free(args);
        return (status);
    }
}