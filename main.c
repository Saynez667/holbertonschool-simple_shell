#include "shell.h"
#include <signal.h>

/**
 * main - Entry point for shell program
 * Return: 0 on success
 */
int main(void)
{
    char *command = NULL;
    char **args = NULL;
    char *full_path = NULL;
    int status = 0;
    char *first_token;

    signal(SIGINT, handle_signal);

    while (1)
    {
        prompt();
        command = read_input();

        if (!command)
            break;

        if (command[0] == '\0' || strcmp(command, "\n") == 0)
        {
            free(command);
            continue;
        }

        /* Get first token to check if command exists */
        first_token = strtok(strdup(command), " \t\r\n\a");
        if (!first_token)
        {
            free(command);
            continue;
        }

        full_path = find_command_in_path(first_token);
        
        if (!full_path)
        {
            if (access(first_token, F_OK) == 0)
                fprintf(stderr, "./hsh: 1: %s: Permission denied\n", first_token);
            else
                fprintf(stderr, "./hsh: 1: %s: not found\n", first_token);
            free(first_token);
            free(command);
            continue;
        }

        free(first_token);
        /* Only parse arguments if command exists */
        args = parse_command(command);
        if (!args)
        {
            free(command);
            free(full_path);
            continue;
        }

        status = execute_command(args, full_path);
        free(full_path);
        free(command);
        free_args(args);
    }

    return (status);
}