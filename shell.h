#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

/* Execute Functions */
char *get_file_path(char *file_name);
int execute_command(char *input, char *argv[],
					char **env, char *program_name);
char *read_input(void);
void print_prompt(void);
int tokenize_input(char *input, char *args[]);

/* String utility functions */
int _strlen(char *str);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
void print_error(char *program, char *cmd, char *msg);
char *concat_path(char *dir, char *command);

/* Built in Functions */
int handle_builtin_commands(char **args,
		int num_args, char *input,
		char **env);
void print_env(char **env);
void handle_cd(char **args, int num_args);
void handle_exit(char *input, int exit_status);
int shell_exit(char **args, char *input);

#endif /* SHELL_H */
