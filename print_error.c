#include "shell.h"

/**
 * print_error - Print error message to stderr
 * @program: Program name
 * @cmd: Command that failed
 * @msg: Error message
 */
void print_error(char *program, char *cmd, char *msg)
{
		write(2, program, _strlen(program));
		write(2, ": 1: ", 4);
		write(2, cmd, _strlen(cmd));
		write(2, ": ", 2);
		write(2, msg, _strlen(msg));
		write(2, "\n", 1);
}
