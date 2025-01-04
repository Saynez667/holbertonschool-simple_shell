#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

extern char **environ;

void sigint_handler(int sig);
int execute_input(char *input);
char *parse_command(char *input);
int execute_command(char *command);

#endif /* SHELL_H */