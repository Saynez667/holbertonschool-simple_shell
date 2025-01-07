#include "shell.h"

/**
 * print_error - Print error message to stderr
 * @program: Program name
 * @cmd: Command that failed
 * @msg: Error message
 */
void print_error(char *program, char *cmd, char *msg)
{
    int i;
    
    for (i = 0; program[i]; i++)
        write(2, &program[i], 1);
    write(2, ": 1: ", 4);
    for (i = 0; cmd[i]; i++)
        write(2, &cmd[i], 1);
    write(2, ": ", 2);
    for (i = 0; msg[i]; i++)
        write(2, &msg[i], 1);
    write(2, "\n", 1);
}