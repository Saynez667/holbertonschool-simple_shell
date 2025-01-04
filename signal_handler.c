#include "shell.h"

/**
 * sigint_handler - Handle SIGINT signal (Ctrl+C)
 * @sig: The signal number
 */
void sigint_handler(int sig)
{
	(void)sig;
	printf("\n$ ");
	fflush(stdout);
}