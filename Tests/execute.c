#include "shell.h"
#include <sys/stat.h>

/**
 * find_command - Searches for a command in the PATH
 * @command: The command to search for
 * Return: Full path of the command if found, NULL otherwise
 */
char *find_command(char *command)
{
    char *path, *path_copy, *path_token, *file_path;
    int command_length, directory_length;
    struct stat buffer;

    path = getenv("PATH");
    if (path)
    {
        path_copy = strdup(path);
        command_length = strlen(command);
        path_token = strtok(path_copy, ":");
        while (path_token != NULL)
        {
            directory_length = strlen(path_token);
            file_path = malloc(command_length + directory_length + 2);
            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, command);
            if (stat(file_path, &buffer) == 0)
            {
                free(path_copy);
                return (file_path);
            }
            free(file_path);
            path_token = strtok(NULL, ":");
        }
        free(path_copy);
        if (stat(command, &buffer) == 0)
            return (strdup(command));
    }
    return (NULL);
}

/**
 * execute - execute command path, child process
 * @args: arguments
 * Return: exit status
 */
int execute(char **args)
{
    int id, status;
    char *command_path;

    if (!args || !args[0])
        return -1;

    command_path = find_command(args[0]);
    if (!command_path)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        return 127;
    }

    id = fork();
    if (id == 0)
    {
        if (execve(command_path, args, environ) == -1)
        {
            perror("Error");
            free(command_path);
            exit(EXIT_FAILURE);
        }
    }
    else if (id < 0)
    {
        perror("Error");
        free(command_path);
        return -1;
    }
    else
    {
        wait(&status);
        free(command_path);
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
    }
    return (status);
}
