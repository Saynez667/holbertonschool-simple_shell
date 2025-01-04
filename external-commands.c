#include "shell.h"

/**
 * execute_external - Execute external commands
 * @args: Array of command arguments
 * 
 * Return: 0 on success, 1 on failure
 */
int execute_external(char **args)
{
    pid_t pid;
    int status;
    char *cmd_path;

    cmd_path = find_executable(args[0]);
    if (cmd_path == NULL)
    {
        fprintf(stderr, "%s: command not found\n", args[0]);
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd_path, args, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    free(cmd_path);
    return (0);
}