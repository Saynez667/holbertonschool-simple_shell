#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
void prompt(void);
char *read_input(void);
char **parse_command(char *command);
int execute_command(char **args);
char *find_command_in_path(const char *command);
void print_env(void);
void change_directory(char **args);
char *_getenv(const char *name, char **environ);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void handle_redirection(char **args);
void _print_error(const char *message);
char *_strdup(const char *str);
int _strcmp(const char *s1, const char *s2);
void free_args(char **args);
int _strlen(const char *s);
char *_strchr(const char *s, int c);
int _atoi(const char *str);

extern char **environ;

#endif