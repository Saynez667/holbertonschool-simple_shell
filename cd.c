#include "shell.h"

/**
  * handle_cd - Handles the cd functionality
  * @args: Array of commands
  * @num_args: Argument count
  */
void handle_cd(char **args, int num_args)
{
	const char *home_dir, *prev_dir, *target_dir;
	char current_dir[1024];

	if (!args)
		return;

	home_dir = getenv("HOME");
	prev_dir = getenv("OLDPWD");

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("cd: getcwd error");
		return;
	}

	target_dir = NULL;
	if (num_args == 1 || strcmp(args[1], "~") == 0)
		target_dir = home_dir;
	else if (strcmp(args[1], "-") == 0)
		target_dir = prev_dir;
	else
		target_dir = args[1];

	if (!target_dir)
	{
		perror("cd: directory path missing or invalid");
		return;
	}

	if (chdir(target_dir) == -1)
		perror("cd");
	else
		setenv("OLDPWD", current_dir, 1);
}
