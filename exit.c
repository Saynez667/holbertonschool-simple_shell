#include "shell.h"

/**
  * handle_exit - Handles the exit functionality
  * @input: Input value to handle
  * @exit_status: Exit status of the code
  */
void handle_exit(char *input, int exit_status)
{
	if (input)
		free(input);
	exit(exit_status);
}

/**
  * shell_exit - Handles the exit status
  * @args: Arguments to the function
  * @input: Input to be freed before exit
  *
  * Return: Should not return, exits the program
  */
int shell_exit(char **args, char *input)
{
	int exit_status = 0;
	int i;

	if (!args || !input)
		return (1);

	if (args[1])
	{
		for (i = 0; args[1][i]; i++)
		{
			if (args[1][i] < '0' || args[1][i] > '9')
			{
				handle_exit(input, 2);
			}
			exit_status = (exit_status * 10) + (args[1][i] - '0');
		}
	}
	handle_exit(input, exit_status);
	return (1);  /* Ne devrait jamais être atteint */
}
