#include "shell.h"

/**
 * handle_path - Finds the path of the command to execute
 * @input: User input
 * Return: The full path of the command if found, NULL otherwise
 */
char *handle_path(const char *input)
{
    if (strchr(input, '/') != NULL)
        return strdup(input);

    const char *path = getenv("PATH");
    if (!path)
        return NULL;

    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        char *result = malloc(strlen(dir) + strlen(input) + 2);
        if (result == NULL)
        {
            perror("Malloc failed");
            free(path_copy);
            return NULL;
        }

        snprintf(result, strlen(dir) + strlen(input) + 2, "%s/%s", dir, input);
        if (access(result, X_OK) == 0)
        {
            free(path_copy);
            return result;
        }

        free(result);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
