#include "shell.h"

/**
 * print_env - Prints all environment variables
 *
 * Return: void
 */
void print_env(void)
{
	int i;

	if (!environ)
	{
		fprintf(stderr, "Environment not available\n");
		return;
	}

	for (i = 0; environ[i]; i++)
	{
		if (write(STDOUT_FILENO, environ[i], _strlen(environ[i])) == -1 ||
			write(STDOUT_FILENO, "\n", 1) == -1)
		{
			perror("write");
			return;
		}
	}
}