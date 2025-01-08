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
 * get_file_path - Get's the full path of the file
 * @command: Command to find
 *
 * Return: Full path of command or NULL if not found
 */
char *get_file_path(char *command)
{
	char *path = NULL;
	char *path_copy = NULL;
	char *path_token = NULL;
	char *file_path = NULL;
	struct stat st;

	if (!command || command[0] == '\0')
		return (NULL);

	/* Check if command is already a path */
	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
			return (_strdup(command));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	path_token = strtok(path_copy, ":");
	while (path_token)
	{
		file_path = concat_path(path_token, command);
		if (file_path && stat(file_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	/* If not found in PATH, try current directory */
	if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
		return (_strdup(command));

	return (NULL);
}
