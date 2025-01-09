#include "shell.h"

/**
 * handle_sigint - Signal handler for SIGINT (Ctrl+C)
 * @sig: Signal number
 */
void handle_sigint(int sig)
{
	(void)sig;  /* Avoid unused parameter warning */
	write(STDOUT_FILENO, "\n", 1);
	print_prompt();
	fflush(stdout);
}

/**
 * setup_signal_handlers - Sets up signal handlers for the shell
 */
void setup_signal_handlers(void)
{
	/* Set up SIGINT handler */
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
}
