#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64

/**
 * main - Simple shell program
 *
 * Return: Always 0.
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGUMENTS];
    char *token;
    int status;

    while (1)
    {
        printf("$ ");
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        token = strtok(command, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGUMENTS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (i > 0)
        {
            if (strcmp(args[0], "exit") == 0)
            {
                break;
            }

            pid_t pid = fork();
            if (pid == 0)
            {
                if (execvp(args[0], args) == -1)
                {
                    perror("Error");
                    exit(EXIT_FAILURE);
                }
            }
            else if (pid < 0)
            {
                perror("Error");
            }
            else
            {
                waitpid(pid, &status, 0);
            }
        }
    }

    return (0);
}
