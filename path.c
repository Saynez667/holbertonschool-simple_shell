#include "shell.h"
#include <sys/stat.h>

/**
 * find_command_in_path - Search for command in PATH
 * @command: Command to search
 * Return: Full path if found, NULL otherwise
 */
char *find_command_in_path(const char *command)
{
    char *path, *path_copy, *dir, *full_path;
    struct stat st;

    if (!command)
        return (NULL);

    if (command[0] == '/')
    {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return (_strdup(command));
        return (NULL);
    }

    path = _getenv("PATH", environ);
    if (!path)
        return (NULL);

    path_copy = _strdup(path);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(_strlen(dir) + _strlen(command) + 2);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }
        sprintf(full_path, "%s/%s", dir, command);
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
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