#include "shell.h"
#include <sys/stat.h>
#include <unistd.h>

/**
 * find_command_in_path - Search for the command in PATH directories
 * @command: The command to search for
 *
 * Return: The full path of the command if found, otherwise NULL
 * Note: The caller is responsible for freeing the returned string
 */
char *find_command_in_path(const char *command)
{
	char *path, *path_copy, *dir, *full_path;
	int path_length;

	if (command[0] == '/' && access(command, X_OK) == 0)
		return (strdup(command));

	path = _getenv("PATH", environ);
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
	{
		perror("strdup");
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}

		path_length = snprintf(full_path, strlen(dir) + strlen(command) + 2,
				       "%s/%s", dir, command);
		if (path_length < 0)
		{
			free(full_path);
			dir = strtok(NULL, ":");
			continue;
		}

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
