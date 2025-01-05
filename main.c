#include "shell.h"

int main(void)
{
    char *buff = NULL, **args;
    size_t read_size = 0;
    ssize_t buff_size = 0;
    int exit_status = 0;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("hsh$ ");

        buff_size = getline(&buff, &read_size, stdin);
        if (buff_size == -1 || _strcmp("exit\n", buff) == 0)
        {
            free(buff);
            break;
        }
        buff[buff_size - 1] = '\0';

        if (_strcmp("_env", buff) == 0)
        {
            _env();
            continue;
        }

        if (empty_line(buff) == 1)
        {
            exit_status = 0;
            continue;
        }

        args = tokenize(buff);
        if (args[0] != NULL)
        {
            char *cmd_path = search_path(args[0]);
            if (cmd_path)
            {
                args[0] = cmd_path;
                exit_status = execute(args);
                if (cmd_path != args[0])
                    free(cmd_path);
            }
            else
                fprintf(stderr, "hsh: %s: command not found\n", args[0]);
        }
        free(args);
    }
    free(buff);
    return (exit_status);
}