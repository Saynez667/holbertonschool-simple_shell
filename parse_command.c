#include "shell.h"

/**
 * parse_command - Parse the input to extract the command
 * @input: The input string to parse
 *
 * Description: This function takes the input string and extracts
 * the first word as the command, ignoring any additional arguments.
 *
 * Return: The parsed command, or NULL if no command found
 */
char *parse_command(char *input)
{
	return (strtok(input, " \t\r\n\a"));
}
