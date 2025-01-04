#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

#define MAX_CMD_LEN 1024

/* Déclaration des fonctions */
void display_prompt(void);
void handle_error(const char *msg);
void execute_command(char *cmd);

#endif /* SHELL_H */
