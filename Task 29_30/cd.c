#include "shell.h"

/**
 * update_oldpwd - Updates the OLDPWD environment variable
 * @current_dir: Current directory path to set as OLDPWD
 *
 * Return: void
 */
void update_oldpwd(const char *current_dir)
{
	if (current_dir)
		setenv("OLDPWD", current_dir, 1);
}

/**
 * save_current_dir - Saves current directory path
 * @buf: Buffer to store current directory path
 * @size: Size of buffer
 *
 * Return: 1 on success, 0 on failure
 */
int save_current_dir(char *buf, size_t size)
{
	if (!buf || getcwd(buf, size) == NULL)
	{
		perror("cd: getcwd error");
		return (0);
	}
	return (1);
}

/**
 * handle_cd - Handles the cd functionality
 * @args: Array of commands
 * @num_args: Argument count
 * @env: Environment variables array
 *
 * Return: void
 */
void handle_cd(char **args, int num_args, char **env)
{
	const char *home_dir, *prev_dir;
	char current_dir[4096];
	int chdir_status;

	if (!args || !save_current_dir(current_dir, sizeof(current_dir)))
		return;

	home_dir = _getenv("HOME", env);
	prev_dir = _getenv("OLDPWD", env);

	if (num_args == 1 || (num_args == 2 && strcmp(args[1], "~") == 0))
	{
		if (!home_dir)
		{
			perror("cd: HOME not set");
			return;
		}
		chdir_status = chdir(home_dir);
	}
	else if (num_args == 2 && strcmp(args[1], "-") == 0)
	{
		if (!prev_dir)
		{
			perror("cd: OLDPWD not set");
			return;
		}
		chdir_status = chdir(prev_dir);
		if (chdir_status == 0)
			write(STDOUT_FILENO, prev_dir, _strlen((char *)prev_dir));
	}
	else
		chdir_status = chdir(args[1]);

	if (chdir_status != 0)
	{
		perror("cd");
		return;
	}

	update_oldpwd(current_dir);
}
