#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFF_SIZE 1024
#define TOK_BUFF_SIZE 64
#define TOK_DELIM " \t\n"

/* Function prototypes */
char *get_location(char *command);
char **split_line(char *line, int *token_count);
void free_tokens(char **tokens, int token_count);

/**
 * get_location - Searches for a command in PATH directories
 * @command: The command to find
 *
 * Return: Full path of command if found, NULL otherwise
 */
char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_len, directory_len;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	command_len = strlen(command);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		directory_len = strlen(path_token);
		file_path = malloc(directory_len + command_len + 2);
		if (file_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, command);

		if (access(file_path, X_OK) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * split_line - Splits a line into tokens
 * @line: The line to split
 * @token_count: Pointer to store number of tokens
 *
 * Return: Array of tokens
 */
char **split_line(char *line, int *token_count)
{
	char **tokens = malloc(TOK_BUFF_SIZE * sizeof(char *));
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, TOK_DELIM);
	*token_count = 0;

	while (token != NULL && *token_count < TOK_BUFF_SIZE - 1)
	{
		tokens[*token_count] = strdup(token);
		if (!tokens[*token_count])
		{
			free_tokens(tokens, *token_count);
			return (NULL);
		}
		(*token_count)++;
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[*token_count] = NULL;
	return (tokens);
}

/**
 * free_tokens - Frees array of tokens
 * @tokens: Array of tokens to free
 * @token_count: Number of tokens
 */
void free_tokens(char **tokens, int token_count)
{
	int i;

	for (i = 0; i < token_count; i++)
		free(tokens[i]);
	free(tokens);
}

/**
 * main - Simple shell implementation
 *
 * Return: Always 0
 */
int main(void)
{
	char input[BUFF_SIZE];
	char **tokens;
	char *cmd_path;
	int token_count, status;
	pid_t child_pid;

	while (1)
	{
		printf("$ ");
		if (fgets(input, BUFF_SIZE, stdin) == NULL)
			break;

		input[strcspn(input, "\n")] = '\0';
		if (strlen(input) == 0)
			continue;

		if (strcmp(input, "exit") == 0)
			break;

		tokens = split_line(input, &token_count);
		if (!tokens || token_count == 0)
		{
			free_tokens(tokens, token_count);
			continue;
		}

		cmd_path = get_location(tokens[0]);
		if (!cmd_path)
		{
			printf("%s: command not found\n", tokens[0]);
			free_tokens(tokens, token_count);
			continue;
		}

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			free(cmd_path);
			free_tokens(tokens, token_count);
			continue;
		}

		if (child_pid == 0)
		{
			free(tokens[0]);
			tokens[0] = cmd_path;
			if (execv(tokens[0], tokens) == -1)
			{
				perror("Error:");
				free_tokens(tokens, token_count);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
			free(cmd_path);
		}
		free_tokens(tokens, token_count);
	}
	return (0);
}