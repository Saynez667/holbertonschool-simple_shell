#include "shell.h"

int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

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
