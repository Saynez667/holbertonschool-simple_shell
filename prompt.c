#include "shell.h"

/**
 * prompt - Displays shell prompt if in interactive mode
 *
 * Return: void
 */
void prompt(void)
{
	const char *prompt_str = "ValakShell$ ";

	if (isatty(STDIN_FILENO))
	{
		if (write(STDOUT_FILENO, prompt_str, _strlen(prompt_str)) == -1)
			perror("write");
	}
}