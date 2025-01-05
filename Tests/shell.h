#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* GLOBAL VAR*/
extern char **environ;

/*PROTOTYPES*/
int execute(char **args);
int _strcmp(const char *s1, const char *s2);
void _env(void);
int empty_line(const char *buff);
char **tokenize(char *buff);
char *find_command(char *command);

#endif
