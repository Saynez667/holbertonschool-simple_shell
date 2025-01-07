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

	if (!dir || !command)
		return (NULL);

	dir_len = _strlen(dir);
	cmd_len = _strlen(command);

	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);

	_strcpy(full_path, dir);
	if (dir[dir_len - 1] != '/')
	{
		full_path[dir_len] = '/';
		dir_len++;
	}
	_strcpy(full_path + dir_len, command);

	return (full_path);
}

/**
 * try_path - Try to find command in given directory
 * @dir: Directory to search in
 * @command: Command to find
 * @path_copy: Copy of PATH to free in case of success
 * Return: Path to command if found, NULL otherwise
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

	if (access(full_path, F_OK | X_OK) == 0)
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
