#include "shell.h"

/**
 * sigint_handler - Handle SIGINT signal (Ctrl+C)
 * @sig: The signal number
 *
 * Description: This function is called when a SIGINT signal is received.
 * It prints a new prompt instead of terminating the shell.
 */
void sigint_handler(int sig)
{
	(void)sig;
	printf("\n$ ");
	fflush(stdout);
}
