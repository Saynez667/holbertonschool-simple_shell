#include "shell.h"

/**
 * concat_path - Concatenates directory and command
 * @dir: Directory path
 * @command: Command name
 *
 * Return: Full path or NULL on failure
 */
char *concat_path(char *dir, char *command)
{
	int dir_len, cmd_len;
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
 * trim_spaces - Removes leading and trailing spaces from command
 * @command: Command string to trim
 *
 * Return: Pointer to first non-space character
 */
char *trim_spaces(char *command)
{
	char *end;

	if (!command)
		return (NULL);

	while (*command == ' ')
		command++;

	if (*command == '\0')
		return (command);

	end = command + _strlen(command) - 1;
	while (end > command && *end == ' ')
		end--;

	*(end + 1) = '\0';
	return (command);
}

/**
 * search_path - Search command in PATH directories
 * @command: Command to find
 * @path: PATH environment variable
 *
 * Return: Full path if found, NULL otherwise
 */
char *search_path(char *command, char *path)
{
	char *path_copy, *dir, *full_path;
	struct stat st;

	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		if (*dir == '\0')
			dir = ".";

		full_path = concat_path(dir, command);
		if (full_path && access(full_path, X_OK) == 0)
		{
			if (stat(full_path, &st) == 0)
			{
				free(path_copy);
				return (full_path);
			}
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * get_file_path - Get's the full path of the file
 * @command: Command to find
 * @env: Environment variables array
 *
 * Return: Full path of command or NULL if not found
 */
char *get_file_path(char *command, char **env)
{
	char *path, *full_path;
	struct stat st;

	if (!command)
		return (NULL);

	command = trim_spaces(command);
	if (!command || *command == '\0')
		return (NULL);

	/* For commands with path */
	if (_strchr(command, '/') != NULL)
	{
		if (access(command, F_OK) == 0)
		{
			if (stat(command, &st) == 0)
				return (_strdup(command));
		}
		return (NULL);
	}

	path = _getenv("PATH", env);
	if (!path)
		return (NULL);

	full_path = search_path(command, path);
	return (full_path);
}
