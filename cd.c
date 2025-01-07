#include "shell.h"

/**
  * update_oldpwd - Updates the OLDPWD environment variable
  * @current_dir: Current directory path to set as OLDPWD
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
  * Return: 1 on success, 0 on failure
  */
int save_current_dir(char *buf, size_t size)
{
	if (getcwd(buf, size) == NULL)
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
  */
void handle_cd(char **args, int num_args)
{
	const char *home_dir, *prev_dir;
	char current_dir[4096];

	if (!args)
		return;

	if (!save_current_dir(current_dir, sizeof(current_dir)))
		return;

	home_dir = getenv("HOME");
	prev_dir = getenv("OLDPWD");

	if (num_args == 1 || strcmp(args[1], "~") == 0)
	{
		if (!home_dir)
		{
			perror("cd: HOME not set");
			return;
		}
		if (chdir(home_dir) != 0)
			perror("cd");
	}
	else if (num_args == 2 && strcmp(args[1], "-") == 0)
	{
		if (!prev_dir)
		{
			perror("cd: OLDPWD not set");
			return;
		}
		if (chdir(prev_dir) != 0)
			perror("cd");
	}
	else if (chdir(args[1]) != 0)
		perror("cd");

	update_oldpwd(current_dir);
}
