#include "shell.h"

/**
 * concat_path - Concatenates directory and command
 * @dir: Directory path
 * @command: Command name
 * Return: Full path
 */
char *concat_path(char *dir, char *command)
{
	int dir_len = 0, cmd_len = 0;
	char *full_path;

	dir_len = _strlen(dir);
	cmd_len = _strlen(command);

	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);

	_strcpy(full_path, dir);
	full_path[dir_len] = '/';
	_strcpy(full_path + dir_len + 1, command);

	return (full_path);
}

/**
 * try_path - Try to find command in a directory
 * @dir: Directory to search
 * @command: Command to find
 * @path_copy: PATH copy to free if needed
 * Return: Command path or NULL
 */
char *try_path(char *dir, char *command, char *path_copy)
{
	char *full_path;

	full_path = concat_path(dir, command);
	if (!full_path)
	{
		free(path_copy);
		return (NULL);
	}

	if (check_path(full_path))
	{
		free(path_copy);
		return (full_path);
	}

	free(full_path);
	return (NULL);
}

/**
 * get_file_path - Get's the full path of the file
 * @command: Command to find
 * Return: Full path of command or NULL
 */
char *get_file_path(char *command)
{
	char *path, *path_copy, *dir, *result;

	if (!command)
		return (NULL);

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		result = try_path(dir, command, path_copy);
		if (result)
			return (result);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
