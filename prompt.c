#include "shell.h"

/**
 * print_prompt - Print the prompt to the user
 * Return: void
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "ValakShell$ ", 11);
		fflush(stdout);
	}
}
