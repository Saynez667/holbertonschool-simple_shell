#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

extern char **environ;

/* Déclaration des fonctions */
int main(void);
int execute(char *line_input);
void signal_handler(int signal);

#endif /* SHELL_H */
