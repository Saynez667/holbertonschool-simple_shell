#include "shell.h"

/**
 * get_file_path - Get's the full path of the file
 * @command: Command to find
 * Return: Full path of command or NULL
 */
char *get_file_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	int is_current_or_path;

	if (!command || !*command)
		return (NULL);

	/* Check if command is absolute or relative path */
	is_current_or_path = (command[0] == '/' || 
			(command[0] == '.' && command[1] == '/'));

	if (is_current_or_path)
	{
		if (access(command, X_OK) == 0)
			return (_strdup(command));
		return (NULL);
	}

	/* Get PATH environment variable */
	path = getenv("PATH");
	if (!path)
		return (NULL);

	/* Copy PATH to avoid modifying original */
	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	/* Search command in each directory in PATH */
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(_strlen(dir) + _strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		_strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

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