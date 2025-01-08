#include "shell.h"

/**
 * execute_child - Handles the child process execution
 * @cmd_path: Path to the command to execute
 * @args: Array of arguments
 * @env: Environment variables
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
 * is_executable - Checks if file exists and is executable
 * @path: Path to check
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(char *path)
{
	struct stat st;

	if (!path)
		return (0);

	if (stat(path, &st) == -1)
		return (0);

	if (!S_ISREG(st.st_mode))
		return (0);

	if (!(st.st_mode & S_IXUSR))
	{
		errno = EACCES;
		return (0);
	}

	return (1);
}

/**
 * handle_relative_path - Handles relative path commands (./cmd)
 * @cmd: Command to handle
 *
 * Return: Full path if found and executable, NULL otherwise
 */
char *handle_relative_path(char *cmd)
{
	char *pwd, *full_path;
	size_t pwd_len;

	/* If starts with / or ../, use as is */
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
		return (is_executable(cmd) ? _strdup(cmd) : NULL);

	/* If starts with ./, remove it */
	if (cmd[0] == '.' && cmd[1] == '/')
		cmd += 2;

	/* Get current directory */
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);

	pwd_len = _strlen(pwd);
	full_path = malloc(pwd_len + _strlen(cmd) + 2);
	if (!full_path)
	{
		free(pwd);
		return (NULL);
	}

	_strcpy(full_path, pwd);
	if (pwd[pwd_len - 1] != '/')
		_strcpy(full_path + pwd_len, "/");
	_strcpy(full_path + _strlen(full_path), cmd);

	free(pwd);
	return (is_executable(full_path) ? full_path : NULL);
}

/**
 * handle_command_path - Handles command path resolution
 * @args: Array of arguments
 * @program_name: Name of the shell program
 *
 * Return: Command path or NULL
 */
char *handle_command_path(char **args, char *program_name)
{
	char *cmd_path = NULL;

	if (!args || !args[0])
		return (NULL);

	/* Check if command contains a path */
	if (_strchr(args[0], '/'))
	{
		cmd_path = handle_relative_path(args[0]);
		if (!cmd_path)
		{
			print_error(program_name, args[0],
				errno == EACCES ? "Permission denied" : "not found");
		}
		return (cmd_path);
	}

	/* Search in PATH */
	cmd_path = get_file_path(args[0]);
	if (!cmd_path)
	{
		print_error(program_name, args[0], "not found");
		return (NULL);
	}

	return (cmd_path);
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

	cmd_path = handle_command_path(args, program_name);
	if (!cmd_path)
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
