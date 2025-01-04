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

	signal(SIGINT, sigint_handler);

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
				break;
			}
			else
			{
				perror("getline");
				free(input);
				exit(EXIT_FAILURE);
			}
		}

		input[strcspn(input, "\n")] = 0; /* Remove newline */

		if (execute_input(input) == -1)
			break;
	}

	free(input);
	return (0);
}
