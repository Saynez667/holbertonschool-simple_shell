#include "shell.h"

/**
 * execute_command - Executes a command in a child process
 * @cmd: The command to execute
 *
 * Description: This function creates a child process using fork() and uses
 * execve() to execute the command. If the execution fails, an error message
 * is displayed. The parent process waits for the child to complete.
 */
void execute_command(char *cmd)
{
    pid_t pid = fork();  /* Créer un processus enfant */

    if (pid == -1) {
        handle_error("fork");
        return;
    }

    if (pid == 0) {  /* Processus enfant */
        char *args[] = {cmd, NULL};  /* Pas d'arguments à passer */
        if (execve(cmd, args, environ) == -1) {
            handle_error("execve");
            exit(EXIT_FAILURE);  /* En cas d'échec, quitter l'enfant */
        }
    } else {  /* Processus parent */
        int status;
        waitpid(pid, &status, 0);  /* Attendre la fin du processus enfant */
    }
}
