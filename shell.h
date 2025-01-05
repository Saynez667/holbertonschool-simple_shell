#ifndef SHELL_H
#define SHELL_H

/*LIBRARIES*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* GLOBAL VAR*/
extern char **environ;

/*PROTOTYPES*/
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *search_path(char *command);
char **_split(char *str, char *sep);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *_getenv(char *env_var);
void *_calloc(unsigned int nmemb, unsigned int size);
void _env(void);
int execute(char **args);
int empty_line(char *buff);

#endif
