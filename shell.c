#include "shell.h"

/**
* get_next_command - Extract next command from input buffer
* @input_ptr: Pointer to current position in input buffer
*
* Return: Allocated string containing next command, or NULL
*/
char *get_next_command(char **input_ptr)
{
	char *start = *input_ptr;

	char *end;

	char *command;

	size_t length;

	if (!start || !*start)
		return (NULL);

	/* Find end of current command (next newline) */
	end = strchr(start, '\n');
	if (end)
	{
		length = end - start;
		*input_ptr = end + 1;  /* Move past the newline */
	}
	else
	{
		length = strlen(start);
		*input_ptr = start + length;
	}

	/* Allocate and copy the command */
	command = malloc(length + 1);
	if (!command)
		return (NULL);

	strncpy(command, start, length);
	command[length] = '\0';

	return (command);
}

/**
* process_commands - Process multiple commands from input buffer
* @input_buffer: Buffer containing commands
* @argv: Program arguments
* @env: Environment variables
* @status: Pointer to status variable
*/
void process_commands(char *input_buffer, char *argv[],

char **env, int *status)
{
	char *current_pos = input_buffer;

	char *command;

	while ((command = get_next_command(&current_pos)))
	{
		char *trimmed = trim_spaces(command);

		if (trimmed && *trimmed)

			*status = execute_command(trimmed, argv, env, argv[0]);
		free(command);
	}
}

/**
* main - Simple shell main program
* @argc: Argument count
* @argv: Array of arguments
* @env: Environment variables
*
* Return: Exit status
*/
int main(int argc __attribute__((unused)), char *argv[], char **env)
{
	char *input_buffer = NULL;

	int status = 0;

	int interactive;

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			print_prompt();

		input_buffer = read_input();
		if (!input_buffer)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}

		process_commands(input_buffer, argv, env, &status);
		free(input_buffer);
		input_buffer = NULL;
	}
}
