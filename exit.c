#include "shell.h"

/**
 * is_valid_number - Check if string is a valid numeric argument
 * @str: String to check
 *
 * Return: 1 if valid number, 0 otherwise
 */
int is_valid_number(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	/* Handle negative numbers */
	if (str[0] == '-')
		return (0);  /* Negative numbers not allowed for exit status */

	/* Check that all characters are digits */
	for (i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	return (1);
}

/**
 * string_to_number - Convert string to number
 * @str: String to convert
 *
 * Return: Converted number
 */
int string_to_number(char *str)
{
	int num = 0;
	int i = 0;

	while (str[i])
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}

	return (num);
}

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
	char *error_msg = "Illegal number";

	if (!args || !input)
		return (1);

	/* If exit has an argument */
	if (args[1])
	{
		/* Validate the argument is a proper number */
		if (!is_valid_number(args[1]))
		{
			print_error(args[0], args[1], error_msg);
			handle_exit(input, 2);
		}

		/* Convert the argument to a number */
		exit_status = string_to_number(args[1]);

		/* Handle exit status greater than 255 */
		if (exit_status > 255)
			exit_status = exit_status % 256;
	}

	/* Exit with the determined status */
	handle_exit(input, exit_status);
	return (1);  /* Should never reach here */
}
