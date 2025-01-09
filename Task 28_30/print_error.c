#include "shell.h"

/**
 * print_error - Print error message to stderr
 * @program_name: Name of the program
 * @cmd: Command that failed
 * @error_msg: Error message to display
 *
 * Description: Prints formatted error message with program name,
 * command and error message to standard error
 */
void print_error(char *program_name, char *cmd, char *error_msg)
{
	char line_number[] = ": 1: ";

	if (!program_name || !cmd || !error_msg)
		return;

	/* Write program name */
	write(STDERR_FILENO, program_name, _strlen(program_name));

	/* Write line number */
	write(STDERR_FILENO, line_number, 5);

	/* Write command */
	write(STDERR_FILENO, cmd, _strlen(cmd));

	/* Write separator */
	write(STDERR_FILENO, ": ", 2);

	/* Write error message */
	write(STDERR_FILENO, error_msg, _strlen(error_msg));

	/* Write newline */
	write(STDERR_FILENO, "\n", 1);
}
