#include "shell.h"

#define MAX_PATH_LENGTH 4096

/**
 * update_pwd - Updates the PWD environment variable
 * @new_pwd: New working directory path
 * 
 * Return: 0 on success, -1 on failure
 */
int update_pwd(const char *new_pwd)
{
	if (!new_pwd)
		return (-1);
	
	if (setenv("PWD", new_pwd, 1) == -1)
	{
		perror("cd: setenv PWD failed");
		return (-1);
	}
	return (0);
}

/**
 * update_oldpwd - Updates the OLDPWD environment variable
 * @old_pwd: Old working directory path
 * 
 * Return: 0 on success, -1 on failure
 */
int update_oldpwd(const char *old_pwd)
{
	if (!old_pwd)
		return (-1);
	
	if (setenv("OLDPWD", old_pwd, 1) == -1)
	{
		perror("cd: setenv OLDPWD failed");
		return (-1);
	}
	return (0);
}

/**
 * get_current_dir - Gets the current working directory
 * @buf: Buffer to store the path
 * @size: Size of the buffer
 * 
 * Return: Pointer to buf on success, NULL on failure
 */
char *get_current_dir(char *buf, size_t size)
{
	if (getcwd(buf, size) == NULL)
	{
		perror("cd: getcwd failed");
		return (NULL);
	}
	return (buf);
}

/**
 * change_directory - Changes to specified directory and updates env variables
 * @new_dir: Directory to change to
 * @current_dir: Current working directory buffer
 * 
 * Return: 0 on success, -1 on failure
 */
int change_directory(const char *new_dir, char *current_dir)
{
	if (chdir(new_dir) == -1)
	{
		perror("cd");
		return (-1);
	}

	if (!get_current_dir(current_dir, MAX_PATH_LENGTH))
		return (-1);

	if (update_pwd(current_dir) == -1)
		return (-1);

	return (0);
}

/**
 * handle_cd - Handles the cd command
 * @args: Array of command arguments
 * @num_args: Number of arguments
 * @env: Environment variables
 */
void handle_cd(char **args, int num_args, char **env)
{
	char current_dir[MAX_PATH_LENGTH];
	const char *target_dir;
	const char *home_dir;
	const char *old_pwd;

	/* Get and save current directory */
	if (!get_current_dir(current_dir, sizeof(current_dir)))
		return;

	home_dir = _getenv("HOME", env);
	old_pwd = _getenv("OLDPWD", env);

	if (num_args == 1 || (num_args == 2 && strcmp(args[1], "~") == 0))
	{
		/* cd or cd ~ */
		if (!home_dir)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 16);
			return;
		}
		target_dir = home_dir;
	}
	else if (num_args == 2 && strcmp(args[1], "-") == 0)
	{
		/* cd - */
		if (!old_pwd)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 18);
			return;
		}
		target_dir = old_pwd;
		write(STDOUT_FILENO, old_pwd, _strlen((char *)old_pwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		/* cd with path argument */
		target_dir = args[1];
	}

	/* Update OLDPWD before changing directory */
	if (update_oldpwd(current_dir) == -1)
		return;

	/* Change directory and update PWD */
	if (change_directory(target_dir, current_dir) == -1)
		return;
}
