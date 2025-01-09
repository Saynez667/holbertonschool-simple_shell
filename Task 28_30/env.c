#include "shell.h"

/**
 * _getenv - Gets an environment variable
 * @name: Name of the environment variable
 * @env: Environment variables array
 * Return: Pointer to the value or NULL if not found
 */
char *_getenv(const char *name, char **env)
{
	int i;
	size_t len;

	if (!name || !env)
		return (NULL);

	len = _strlen((char *)name);
	for (i = 0; env[i]; i++)
	{
		if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
	}
	return (NULL);
}

/**
 * print_env - Prints the environment variables
 * @env: Array of environment variables
 *
 * Description: Iterates through environment variables and prints
 * each one followed by a newline
 */
void print_env(char **env)
{
	int i;
	char *env_var;

	if (!env)
		return;

	for (i = 0; env[i]; i++)
	{
		env_var = env[i];
		if (env_var)
		{
			write(STDOUT_FILENO, env_var, _strlen(env_var));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}
