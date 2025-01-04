#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

#define MAX_ARGS 64
#define MAX_PIPES 10

extern char **environ;

void sigint_handler(int sig);
int execute_input(char *input);
char **parse_command(char *command);
int execute_builtin(char **args);
int execute_external(char **args);
char *find_executable(char *cmd);
void handle_redirection(char **args);
int execute_pipeline(char *input);

#endif