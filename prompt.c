#include "shell.h"

/* Color codes */
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

/**
 * print_prompt - Print the prompt to the user
 * Return: void
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, GREEN "Shell" RESET " $ ", 17);
		fflush(stdout);
	}
}
