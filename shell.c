#include "shell.h"

/**
  * main - Wait program
  * @argc: Argumnt count
  * @argv: Array of arguments
  * @env: Environment variable
  *
  * Return: O Always succes
  */
int main(int argc __attribute__((unused)), char *argv[], char **env)
{
    char *input_buffer;
    int status = 0;

    while (1)
    {
        print_prompt();
        input_buffer = read_input();

        if (!input_buffer)
        {
            write(STDOUT_FILENO, "\n", 1);
            return (status);
        }
        
        if (strlen(input_buffer) > 0 && input_buffer[0] != '\n')
        {
            execute_command(input_buffer, argv, env, argv[0]);
            status = 127;  // Set default error status
        }
        free(input_buffer);
    }

    return (status);
}