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
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t nchars_read;

    while (1)
    {
        printf("$ ");
        fflush(stdout);
        nchars_read = getline(&lineptr, &n, stdin);

        if (nchars_read == -1)
        {
            printf("\n");
            break;
        }

        lineptr[strcspn(lineptr, "\n")] = '\0';

        if (strlen(lineptr) == 0)
            continue;

        execute_command(lineptr);
    }

    free(lineptr);
    return (0);
}
