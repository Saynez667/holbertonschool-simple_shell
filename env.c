#include "shell.h"

/**
 * print_env - Prints the environment variables
 * @env: Arguments
 */
void print_env(char **env)
{
	int i;
	char *str;

	while (*env != NULL)
	{
		str = *env;
		for (i = 0; str[i]; i++)
			;
		write(1, str, i);
		write(1, "\n", 1);
		env++;
	}
}
