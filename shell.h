#ifndef SHELL_H
#define SHELL_H

/* LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* MACROS */
#define BUFFER_SIZE 1024

/* PROTOTYPES */
/* Main functions */
void prompt(void);
char *read_input(void);
char **parse_command(char *command);
void execute_command(char **args);
void handle_redirection(char **args);
int execute_builtin(char **args);

/* Path and environment */
char *find_command_in_path(const char *command);
void print_env(void);
void change_directory(char **args);
char *_getenv(const char *name, char **environ);

/* String utilities */
char *_strdup(const char *str);
int _strcmp(const char *s1, const char *s2);
char *_strchr(const char *s, int c);
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);

/* Memory management */
void free_args(char **args);

/* Error handling */
void _print_error(const char *message);
int _atoi(const char *str);

/* GLOBAL_VAR */
extern char **environ;

#endif