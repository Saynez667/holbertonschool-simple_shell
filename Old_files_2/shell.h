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

char *_getenv(const char *env_var);
char *handle_path(char *input);
char *search_path(const char *command);
void *_calloc(unsigned int nmemb, unsigned int size);
void _env(void);
int execute(char **args);
int empty_line(char *buff);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char **_split(char *str, char *sep);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
void _err(char **args);
void _env(void);

#endif
