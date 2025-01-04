#include "shell.h"

/**
 * main - Entry point for the simple shell
 *
 * Description: This function implements the main loop for a simple shell.
 * It continuously prompts the user for input, reads commands, and executes
 * them if they are valid executable files. The loop continues until an EOF
 * is encountered (Ctrl+D) or an error occurs.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char *cmd = NULL;
    size_t len = 0;

    while (1) {
        display_prompt();  /* Afficher le prompt */

        /* Lire la commande entrée par l'utilisateur */
        if (getline(&cmd, &len, stdin) == -1) {
            if (feof(stdin)) {
                /* Si EOF (Ctrl+D), quitter le shell */
                printf("\nExiting shell...\n");
                break;
            }
            handle_error("getline");
            continue;
        }

        /* Supprimer le caractère de nouvelle ligne à la fin de la commande */
        cmd[strcspn(cmd, "\n")] = '\0';

        if (strlen(cmd) == 0) {
            continue;  /* Si la commande est vide, recommencer */
        }

        /* Vérifier si la commande est un fichier exécutable et l'exécuter */
        if (access(cmd, X_OK) == 0) {
            execute_command(cmd);
        } else {
            fprintf(stderr, "Error: command not found: %s\n", cmd);
        }
    }

    free(cmd);  /* Libérer la mémoire allouée pour la commande */
    return (0);
}
