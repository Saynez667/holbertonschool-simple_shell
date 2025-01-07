#include "shell.h"

/**
 * reallocate_tokens - Reallocates memory for tokens array
 * @tokens: Current tokens array
 * @bufsize: Current buffer size
 * @current_size: Number of tokens
 *
 * Return: Reallocated array or NULL on failure
 */
char **reallocate_tokens(char **tokens, int *bufsize, int current_size)
{
	char **new_tokens;

	*bufsize += BUFFER_SIZE;
	new_tokens = _realloc(tokens, current_size * sizeof(char *),
			(*bufsize) * sizeof(char *));
	if (!new_tokens)
	{
		free_args(tokens);
		return (NULL);
	}
	return (new_tokens);
}

/**
 * parse_command - Splits command into tokens
 * @command: Input command string
 *
 * Return: Array of tokens or NULL on failure
 */
char **parse_command(char *command)
{
    int i = 0;
    char **tokens;
    char *token, *command_copy;
    const char *delim = " \t\r\n\a";

    if (!command)
        return (NULL);

    /* Allouer de l'espace pour un maximum de 64 tokens */
    tokens = malloc(64 * sizeof(char *));
    if (!tokens)
        return (NULL);

    command_copy = _strdup(command);
    if (!command_copy)
    {
        free(tokens);
        return (NULL);
    }

    token = strtok(command_copy, delim);
    while (token && i < 63)
    {
        tokens[i] = _strdup(token);
        if (!tokens[i])
        {
            free_args(tokens);
            free(command_copy);
            return (NULL);
        }
        token = strtok(NULL, delim);
        i++;
    }
    tokens[i] = NULL;
    free(command_copy);
    return (tokens);
}