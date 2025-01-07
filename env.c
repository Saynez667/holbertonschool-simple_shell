#include "shell.h"

/**
 * print_env - Prints the environment variables
 * @env: Arguments
 */
void print_env(char **env)
{
	int i;
	char *str;

	if (!env)
		return;

	for (i = 0; env[i] != NULL; i++)
	{
		str = env[i];
		if (str)
		{
			write(STDOUT_FILENO, str, _strlen(str));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}
