#include "shell.h"

/**
 * main - Entry point for the simple shell
 *
 * Description: This function implements the main loop for a simple shell.
 * It reads user commands, processes them, and executes them until the user
 * chooses to exit.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        printf("$ ");
        read = getline(&line, &len, stdin);

        if (read == -1)
        {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
            continue;

        execute_command(line);
    }

    free(line);
    return (0);
}
