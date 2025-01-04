#include "shell.h"

/**
 * find_executable - Find the full path of an executable
 * @cmd: The command to find
 * 
 * Return: The full path of the executable, or NULL if not found
 */
char *find_executable(char *cmd)
{
    char *path, *path_copy, *dir, *full_path;

    path = getenv("PATH");
    path_copy = strdup(path);
    dir = strtok(path_copy, ":");

    while (dir != NULL)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        sprintf(full_path, "%s/%s", dir, cmd);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}