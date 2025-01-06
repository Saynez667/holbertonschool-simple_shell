#include "shell.h"
#include <signal.h>

/**
 * handle_signal - Signal handler for SIGINT
 * @sig: Signal number
 */
void handle_signal(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}