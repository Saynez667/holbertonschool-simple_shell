#include "shell.h"

/**
 * main - Entry point for the simple shell
 *
 * Description: This function runs a simple UNIX command line interpreter.
 * It displays a prompt, waits for user input, and executes simple commands.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read_size;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        read_size = getline(&input, &input_size, stdin);
        if (read_size == -1)
        {
            if (feof(stdin))
            {
                printf("\n");
                break;  // Handle Ctrl+D (EOF)
            }
            else
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        // Check if the command is "exit"
        if (strcmp(input, "exit") == 0)
        {
            break;  // Exit the shell
        }

        // Execute the command
        if (execute_command(input) == -1)
        {
            fprintf(stderr, "%s: command not found\n", input);
        }
    }

    free(input);
    return 0;
}