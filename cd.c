#include "shell.h"

/**
 * change_directory - Changes the current working directory
 * @args: Array of arguments where args[1] is the target directory
 *
 * Return: void
 */
void change_directory(char **args)
{
	char current_dir[BUFFER_SIZE];
	char *target_dir, *old_pwd;

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd");
		return;
	}

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		target_dir = _getenv("HOME", environ);
		if (!target_dir)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return;
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		target_dir = _getenv("OLDPWD", environ);
		if (!target_dir)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return;
		}
		printf("%s\n", target_dir);
	}
	else
		target_dir = args[1];

	if (chdir(target_dir) == -1)
	{
		perror("cd");
		return;
	}

	if (setenv("OLDPWD", current_dir, 1) == -1)
		perror("setenv OLDPWD");
	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
	{
		if (setenv("PWD", current_dir, 1) == -1)
			perror("setenv PWD");
	}
}