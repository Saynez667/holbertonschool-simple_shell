#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Macros */
#define BUFFER_SIZE 1024

/* Input/Output functions */
void prompt(void);
char *read_input(void);
void _print_error(const char *message);

/* Command processing functions */
char **parse_command(char *command);
int execute_command(char **args);
char *find_command_in_path(const char *command);
int execute_builtin(char **args);

/* Built-in commands */
void print_env(void);
void change_directory(char **args);

/* Environment functions */
char *_getenv(const char *name, char **environ);

/* Memory management */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_args(char **args);

/* String utilities */
char *_strdup(const char *str);
int _strcmp(const char *s1, const char *s2);
int _strlen(const char *s);
char *_strchr(const char *s, int c);
int _atoi(const char *str);

/* Signal handling */
void handle_signal(int sig);

/* Global variables */
extern char **environ;

#endif /* SHELL_H */