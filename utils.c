#include "shell.h"

void _env(void)
{
    char **env = environ;
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}

int empty_line(const char *buff)
{
    while (*buff)
    {
        if (*buff != ' ' && *buff != '\t' && *buff != '\n')
            return 0;
        buff++;
    }
    return 1;
}

char **tokenize(char *buff)
{
    char **tokens = malloc(64 * sizeof(char *));
    char *token;
    int i = 0;

    if (!tokens)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token = strtok(buff, " \t\n");
    while (token != NULL)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL;
    return tokens;
}
