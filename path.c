#include "shell.h"

/**
 * check_path_type - Checks if command starts with / or ./
 * @str: The command to check
 * Return: 1 if absolute/relative path, 0 if command name only
 */
int check_path_type(const char *str)
{
    if (!str)
        return (0);
    
    if (str[0] == '/' || (str[0] == '.' && str[1] == '/'))
        return (1);
        
    return (0);
}

/**
 * get_file_loc - Get the executable path of file
 * @path: Full path variable
 * @file_name: The executable file
 * Return: Full path to the executable file
 */
char *get_file_loc(char *path, char *file_name)
{
    char *path_copy, *token, *path_buffer = NULL;
    struct stat file_path;

    path_copy = strdup(path);
    if (!path_copy)
        return (NULL);

    token = strtok(path_copy, ":");
    while (token)
    {
        path_buffer = malloc(strlen(token) + strlen(file_name) + 2);
        if (!path_buffer)
        {
            free(path_copy);
            return (NULL);
        }
        sprintf(path_buffer, "%s/%s", token, file_name);

        if (stat(path_buffer, &file_path) == 0 && access(path_buffer, X_OK) == 0)
        {
            free(path_copy);
            return (path_buffer);
        }
        free(path_buffer);
        token = strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}

/**
 * get_file_path - Get's the full path of the file
 * @file_name: Argument name
 * Return: The full path argument to the file
 */
char *get_file_path(char *command)
{
    char *path, *path_copy, *dir, *full_path;
    struct stat st;

    path = getenv("PATH");
    if (!path)
        return (NULL);

    path_copy = strdup(path);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }
        sprintf(full_path, "%s/%s", dir, command);
        
        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}