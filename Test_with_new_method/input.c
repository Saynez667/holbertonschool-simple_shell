#include "shell.h"

/**
 * read_input - reads user input
 * Return: input string
 */
char *read_input(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    characters = getline(&line, &bufsize, stdin);
    if (characters == -1)
    {
        if (feof(stdin))
        {
            free(line);
            return NULL; // EOF atteint, sortie normale
        }
        else
        {
            perror("Erreur lors de la lecture de l'entrée");
            free(line);
            return NULL;
        }
    }
    return (line);
}