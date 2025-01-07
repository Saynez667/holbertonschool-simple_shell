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

        /* Correct handling of Ctrl+D (EOF) */
        if (!command)
        {
            write(STDOUT_FILENO, "\n", 1);  /* Print newline on EOF */
            break;  /* Exit the loop */
        }

        if (command[0] == '\0' || strcmp(command, "\n") == 0)
        {
            free(command);
            continue;
        }

        first_token = strtok(strdup(command), " \t\r\n\a");
        if (!first_token)
        {
            free(command);
            continue;
        }

        /* Vérification de la commande dans PATH */
        full_path = find_command_in_path(first_token);
        if (!full_path && first_token[0] != '/')
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", first_token);
            free(first_token);
            free(command);
            continue;
        }

        /* Si c'est un chemin absolu, vérifier directement */
        if (first_token[0] == '/' && access(first_token, F_OK) != 0)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", first_token);
            free(first_token);
            free(command);
            continue;
        }

        if (access(full_path ? full_path : first_token, X_OK) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: Permission denied\n", first_token);
            free(first_token);
            free(command);
            free(full_path);
            continue;
        }

        free(first_token);
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