#include "shell.h"

/**
 * main - Simple UNIX command line interpreter
 *
 * Return: 0 on success
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int status;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (feof(stdin))
            {
                free(line);
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("./hsh");
                free(line);
                exit(EXIT_FAILURE);
            }
        }

        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0)
            continue;

        status = execute(line);
        if (status == -1)
            fprintf(stderr, "./hsh: 1: %s: not found\n", line);
    }

    free(line);
    return (0);
}
