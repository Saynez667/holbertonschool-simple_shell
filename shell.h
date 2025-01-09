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
int execute_command(char *input, char *argv[],
		char **env, char *program_name);
void execute_child(char *cmd_path, char **args, char **env);
char *handle_command_path(char **args, char *program_name);
int get_token_count(char **args);

/* Input and Tokenization Functions */
char *read_input(void);
void print_prompt(void);
int tokenize_input(char *input, char *args[]);
void free_tokens(char **args, int count);
char *trim_token(char *token);

/* Path Functions */
char *get_file_path(char *command);
char *search_path(char *command, char *path);
char *check_current_dir(char *command);
char *trim_spaces(char *command);
char *concat_path(char *dir, char *command);

/* String utility functions */
int _strlen(char *str);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
char *_strchr(const char *s, int c);
char *_memset(char *s, char b, unsigned int n);

/* Error Handling Functions */
void print_error(char *program, char *cmd, char *msg);

/* Built in Functions */
int handle_builtin_commands(char **args,
		int num_args, char *input,
		char **env);
void print_env(char **env);
void handle_cd(char **args, int num_args);
void handle_exit(char *input, int exit_status);
int shell_exit(char **args, char *input);

#endif /* SHELL_H */
