#include "shell.h"

/**
 * tokenize - Splits a string into tokens
 * @line_input: The string to tokenize
 *
 * Return: An array of strings
 */
char **tokenize(char *line_input)
{
    char **tokens = NULL;
    char *token;
    int i = 0;
    
    tokens = malloc(sizeof(char *) * 64);
    if (!tokens)
        return NULL;
    
    token = strtok(line_input, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[i] = NULL;
    return tokens;
}

/**
 * free_tokens - Frees the memory allocated for tokens
 * @tokens: The array of tokens to free
 */
void free_tokens(char **tokens)
{
    int i;
    
    if (!tokens)
        return;
    
    for (i = 0; tokens[i]; i++)
        free(tokens[i]);
    free(tokens);
}

/**
 * signal_handler - Handles the SIGINT signal
 * @signal: The signal number
 */
void signal_handler(int signal)
{
    (void)signal;
    write(STDOUT_FILENO, "\nsimpleshell$ ", 14);
}

/**
 * print_env - Prints the current environment
 */
void print_env(void)
{
    int i = 0;
    
    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }
}
