#include "shell.h"

/**
 * execute_command - Execute command with arguments
 * @args: Command and arguments
 * @full_path: Full path of the command
 *
 * Return: Exit status
 */
int execute_command(char **args, char *full_path)
{
    pid_t child_pid;
    int status;

    /* Validate arguments */
    if (!args || !args[0] || !full_path)
        return (1); /* Pas de fork */

    /* Check if command exists and is executable */
    if (access(full_path, F_OK) == -1)
        return (126); /* Pas de fork */

    /* Create child process */
    child_pid = fork(); /* Fork uniquement si tout est OK */
    if (child_pid == -1)
    {
        perror("fork");
        return (1);
    }

    if (child_pid == 0)
    {
        /* Execute command in child process */
        if (execve(full_path, args, environ) == -1)
        {
            perror("execve");
            exit(127);
        }
    }
    else
    {
        /* Wait for child process to complete */
        wait(&status);
        return (WEXITSTATUS(status));
    }

    return (1);  /* Should never reach here */
}
