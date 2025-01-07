#include "shell.h"

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
