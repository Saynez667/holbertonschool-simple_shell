#include "shell.h"
#include <sys/stat.h>
#include <unistd.h>

/**
 * find_command_in_path - Search for the command in the directories of the PATH
 * @command: The command to search for
 * Return: The full path of the command if found, otherwise NULL
 * Note: The caller is responsible for freeing the returned string
 */
char *find_command_in_path(const char *command)
{
    char *path, *path_copy, *dir;
    char full_path[BUFFER_SIZE];
    
    // Check if command is already a path
    if (command[0] == '/')
    {
        if (access(command, X_OK) == 0)
            return strdup(command);
        return NULL;
    }

    path = _getenv("PATH", environ);
    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy)
    {
        perror("strdup");
        return NULL;
    }

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        if (snprintf(full_path, sizeof(full_path), "%s/%s", dir, command) >= sizeof(full_path))
        {
            // Path too long, skip this directory
            dir = strtok(NULL, ":");
            continue;
        }

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return strdup(full_path);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
