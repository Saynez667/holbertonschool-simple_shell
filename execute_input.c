#include "shell.h"

/**
 * execute_input - Execute the user input
 * @input: The user input string
 *
 * Description: This function takes the user input, parses it to extract
 * the command, and then executes the command. It handles the "exit" command
 * and properly manages errors and memory.
 *
 * Return: 0 on success, -1 on exit command or failure
 */
int execute_input(char *input)
{
    char *command = parse_command(input);
    int result;

    if (command == NULL)
    {
        return (0);
    }

    if (strcmp(command, "exit") == 0)
    {
        free(command);
        return (-1);
    }

    result = execute_command(command);
    if (result == -1)
    {
        fprintf(stderr, "%s: command not found\n", command);
    }

    free(command);
    return (result);
}
