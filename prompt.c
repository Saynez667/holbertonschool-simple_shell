#include "shell.h"

/**
  * print_prompt - Print the prompt to the user
  */
void print_prompt(void)
{
  /* isatty() vérifie si STDIN est un terminal */
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "ValakShell$ ", 12);
}
