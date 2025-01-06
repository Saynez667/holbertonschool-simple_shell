#include "shell.h"
#include <sys/stat.h>
#include <unistd.h>

extern char **environ;

/**
 * find_command_in_path - Search for the command in PATH directories
 * @command: The command to search for
 *
 * Return: The full path of the command if found, otherwise NULL
 * Note: The caller is responsible for freeing the returned string
 */
char *find_command_in_path(const char *command)
{
    char *path = _getenv("PATH", environ);
    char *path_copy, *dir, *full_path;
    struct stat st;

    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (full_path)
        {
            sprintf(full_path, "%s/%s", dir, command);
            if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
            {
                free(path_copy);
                return full_path;
            }
            free(full_path);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
