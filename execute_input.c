#include "shell.h"

/**
 * execute_input - Execute the user input
 * @input: The user input string
 *
 * Description: This function takes the user input, parses it to extract
 * the command, and then executes the command.
 *
 * Return: 0 on success, -1 on failure
 */
int execute_input(char *input)
{
	char *command = parse_command(input);

	if (command == NULL)
	{
		return (0);
	}

	return (execute_command(command));
}
