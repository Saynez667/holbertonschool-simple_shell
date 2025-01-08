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
	char *error_msg = "Illegal number";

	if (!args || !input)
		return (1);

	if (args[1])
	{
		if (args[1][0] == '-')
		{
			print_error(args[0], args[1], error_msg);
			handle_exit(input, 2);
		}

		for (i = 0; args[1][i]; i++)
		{
			if (args[1][i] < '0' || args[1][i] > '9')
			{
				print_error(args[0], args[1], error_msg);
				handle_exit(input, 2);
			}
			exit_status = (exit_status * 10) + (args[1][i] - '0');
		}

		if (exit_status > 255)
			exit_status = exit_status % 256;
	}

	handle_exit(input, exit_status);
	return (1);
}
