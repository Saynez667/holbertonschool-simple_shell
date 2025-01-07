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

    if (!args || !args[0] || !full_path)
        return (1);

    child_pid = fork();
    if (child_pid == -1)
        return (1);

    if (child_pid == 0)
    {
        execve(full_path, args, environ);
        perror("execve");
        exit(126);
    }

    wait(&status);
    return (WEXITSTATUS(status));
}