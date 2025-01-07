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
		write(STDERR_FILENO, program_name, _strlen(program_name));
		write(STDERR_FILENO, ": 1: ", 5);
		write(STDERR_FILENO, cmd, _strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
		write(STDERR_FILENO, "\n", 1);
}
