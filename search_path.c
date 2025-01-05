#include "shell.h"

/**
 * search_path - search file between the path
 * @command: cmd
 * Return: cmd path
 */

char *search_path(char *command)
{
	char *path = _getenv("PATH"), *path_cpy;
	char **path_split;
	char *path_concat = NULL;
	int i = 0, path_len = 0;
	struct stat info;

	if (stat(command, &info) == 0)
		return _strdup(command);

		if (!path)
        return NULL;

    path_cpy = _strdup(path);
    if (!path_cpy)
        return NULL;

	path_split = _split(path_cpy, ":");

	while (path_split[i])
	{
		path_concat = malloc(strlen(path_split[i]) + strlen(command) + 2);
        if (!path_concat)
        {
            free(path_cpy);
            free(path_split);
            return NULL;
        }
        sprintf(path_concat, "%s/%s", path_split[i], command);

        if (stat(path_concat, &info) == 0)
        {
            free(path_cpy);
            free(path_split);
            return path_concat;
        }

        free(path_concat);
        i++;
    }

    free(path_cpy);
    free(path_split);
    return NULL;
}