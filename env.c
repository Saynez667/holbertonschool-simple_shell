#include "shell.h"

/**
 * print_env - Prints the environment variables
 * @env: Array of environment variables
 */
void print_env(char **env)
{
	int i;
	char *str;

	if (!env)
		return;

	for (i = 0; env[i]; i++)
	{
		str = env[i];
		if (str)
		{
			write(STDOUT_FILENO, str, _strlen(str));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}
