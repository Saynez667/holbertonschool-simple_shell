#include "shell.h"

/**
 * find_executable - Find the full path of an executable
 * @cmd: The command to find
 *
 * Description: This function searches for the full path of an executable
 * command in the directories specified by the PATH environment variable.
 * It iterates through each directory in PATH, constructs the full path,
 * and checks if the file exists and is executable.
 *
 * Return: A dynamically allocated string containing the full path of the
 * executable if found, or NULL if the executable is not found in any
 * directory in PATH. The caller is responsible for freeing the returned
 * string.
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