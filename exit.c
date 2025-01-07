#include "shell.h"
/**
  * handle_exit - Handles the exit functionality
  * @input: Input value to handle
  * @exit_status: Exit status of the code
  */
void handle_exit(char *input, int exit_status)
{
	free(input);
	exit(exit_status);
}

/**
  * shell_exit - Handles the exit status
  * @args: Arguments to the function
  * @input: Checks the status of exit
  *
  * Return: Status of exit, 1 if otherwise
  */
int shell_exit(char **args, char *input)
{
	char *status_str;
	int exit_status, i;

	if (args[1] != NULL)
	{
		exit_status = 0;
		status_str = args[1];

		for (i = 0; status_str[i] != '\0'; i++)
		{
			if (status_str[i] < '0' || status_str[i] > '9')
			{
				handle_exit(input, 2);
				return (1);
			}
			exit_status = exit_status * 10 + (status_str[i] - '0');
		}
		handle_exit(input, exit_status);
	}
	else
	{
		handle_exit(input, 127);
	}
	return (1);
}