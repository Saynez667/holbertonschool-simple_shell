#include "shell.h"

/**
 * print_env - Prints the environment variables
 * @env: Arguments
 */
void print_env(char **env)
{
    while (*env != NULL)
    {
        write(1, *env, strlen(*env));
        write(1, "\n", 1);
        env++;
    }
}
