#include "shell.h"

/**
 * prompt - display user prompt
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("ValakShell$ ");
		fflush(stdout);
	}
}