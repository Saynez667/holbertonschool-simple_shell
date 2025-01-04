#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 *
 * Description: This function displays the prompt "$ " to the user,
 * inviting them to enter a command. It ensures the prompt is immediately
 * visible by flushing the output buffer.
 */
void display_prompt(void)
{
    printf("$ ");
    fflush(stdout);
}

/**
 * handle_error - Handles errors by displaying an error message
 * @msg: The error message to display
 *
 * Description: This function uses perror to display an error message
 * along with the string passed as an argument. It provides additional
 * context about the nature of the error.
 */
void handle_error(const char *msg)
{
    perror(msg);
}
