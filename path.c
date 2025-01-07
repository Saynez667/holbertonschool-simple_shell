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
	/* Add slash only if directory doesn't end with one */
	if (dir[dir_len - 1] != '/')
	{
		full_path[dir_len] = '/';
		dir_len++;
	}
	_strcpy(full_path + dir_len, command);

	return (full_path);
}

/**
 * get_file_path - Get's the full path of the file
 * @command: Command to find
 * Return: Full path of command or NULL
 */
char *get_file_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	struct stat st;

	if (!command)
		return (NULL);

	/* Check if command exists in current directory */
	if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
		return (_strdup(command));

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = concat_path(dir, command);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

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