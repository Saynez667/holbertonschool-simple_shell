#include "shell.h"

/**
 * setup_ls_colors - Sets up environment for colored ls output
 * @args: Command arguments
 * @env: Environment variables array
 * @num_args: Number of arguments
 *
 * Return: void
 */
void setup_ls_colors(char **args, char **env, int num_args)
{
	char *ls_colors, *color_string;
	int i;

	if (!args || !args[0] || strcmp(args[0], "ls") != 0)
		return;

	for (i = 0; i < num_args; i++)
		if (strstr(args[i], "--color") != NULL)
			return;

	if (num_args < 9)
	{
		args[num_args] = "--color=auto";
		args[num_args + 1] = NULL;
	}

	ls_colors = _getenv("LS_COLORS", env);
	if (!ls_colors || !*ls_colors)
	{
		color_string = "di=34:ln=35:so=32:pi=33:ex=31:bd=34;46:";
		color_string = "cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43";
		setenv("LS_COLORS", color_string, 1);
	}
}

/**
 * execute_child - Handles the child process execution
 * @cmd_path: Path to the command to execute
 * @args: Array of arguments
 * @env: Environment variables
 *
 * Return: void
 */
void execute_child(char *cmd_path, char **args, char **env)
{
	if (execve(cmd_path, args, env) == -1)
	{
		perror("Error");
		free(cmd_path);
		free_tokens(args, get_token_count(args));
		exit(127);
	}
}

/**
 * handle_command_path - Handles command path resolution using stat
 * @args: Array of arguments
 * @program_name: Name of the shell program
 * @env: Environment variables array
 *
 * Return: Command path or NULL
 */
char *handle_command_path(char **args, char *program_name, char **env)
{
	char *cmd_path;

	if (!args[0])
		return (NULL);

	cmd_path = get_file_path(args[0], env);
	if (!cmd_path)
	{
		print_error(program_name, args[0], "not found");
		return (NULL);
	}

	return (cmd_path);
}

/**
 * get_token_count - Count number of tokens
 * @args: Array of tokens
 *
 * Return: Number of tokens
 */
int get_token_count(char **args)
{
	int count = 0;

	if (!args)
		return (0);

	while (args[count])
		count++;

	return (count);
}

/**
 * execute_command - Executes the input from the buffer
 * @input: The argument from the buffer
 * @argv: Array of argument
 * @env: Environment variables
 * @program_name: Name of the shell program
 *
 * Return: Exit status of the command
 */
int execute_command(char *input, char *argv[] __attribute__((unused)),
		char **env, char *program_name)
{
	char *args[10];
	char *cmd_path = NULL;
	int status = 0, num_args;
	pid_t child_pid;

	num_args = tokenize_input(input, args);
	if (num_args == 0)
		return (0);

	if (handle_builtin_commands(args, num_args, input, env) == 1)
	{
		free_tokens(args, num_args);
		return (0);
	}

	setup_ls_colors(args, env, num_args);

	cmd_path = handle_command_path(args, program_name, env);
	if (cmd_path == NULL)
	{
		free_tokens(args, num_args);
		return (127);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		free(cmd_path);
		free_tokens(args, num_args);
		return (1);
	}

	if (child_pid == 0)
		execute_child(cmd_path, args, env);

	waitpid(child_pid, &status, 0);
	free(cmd_path);
	free_tokens(args, num_args);
	return (WEXITSTATUS(status));
}
