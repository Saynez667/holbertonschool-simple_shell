#include "shell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * find_command_in_path - Search for command in PATH directories
 * @command: Command to search for
 *
 * Return: Full path if found, NULL otherwise
 */
char *find_command_in_path(const char *command)
{
	char *path = _getenv("PATH", environ);
	char *path_copy, *dir, *full_path;
	struct stat st;

	if (!command || !path)
		return (NULL);

	/* Check if command is absolute or relative path */
	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
			return (_strdup(command));
		return (NULL);
	}

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