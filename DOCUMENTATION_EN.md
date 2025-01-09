# Detailed Documentation of Simple Shell

## Table of Contents
1. [Program Startup](#1-program-startup)
2. [Prompt Display](#2-prompt-display)
3. [Input Reading](#3-input-reading)
4. [Input Processing](#4-input-processing)
5. [Builtin Commands Check](#5-builtin-commands-check)
6. [Command Search](#6-command-search)
7. [Command Execution](#7-command-execution)
8. [Error Handling](#8-error-handling)
9. [Utility Functions](#9-utility-functions)
10. [CD Management](#10-cd-management)
11. [Environment Management](#11-environment-management)

## 1. Program Startup
**File**: `shell.c`
```c
int main(int argc, char *argv[], char **env)
```
**Purpose**:
- Program entry point
- Checks interactive mode using `isatty()`
- Initializes the main shell loop
- Handles command line arguments and environment

**Key Operations**:
- Sets up the shell environment
- Determines shell mode (interactive/non-interactive)
- Establishes signal handlers
- Manages the main program loop

## 2. Prompt Display
**File**: `prompt.c`
```c
void print_prompt(void)
```
**Purpose**:
- Displays "Shell$ " in interactive mode
- Uses `write()` for display
- Ensures prompt visibility with `fflush()`

**Key Operations**:
- Checks if running in interactive mode
- Writes prompt to STDOUT
- Flushes output buffer

## 3. Input Reading
**File**: `input.c`
```c
char *read_input(void)
```
**Purpose**:
- Reads user input using `getline()`
- Handles special cases:
  * EOF (Ctrl+D)
  * Empty lines
  * Newline characters

**Key Operations**:
- Allocates input buffer
- Reads line from standard input
- Processes and cleans input
- Handles memory management

## 4. Input Processing
**File**: `tokenize.c`
```c
int tokenize_input(char *input, char *args[])
void free_tokens(char **tokens, int count)
char *trim_token(char *token)
```
**Purpose**:
- Splits command into tokens
- Cleans excess whitespace
- Limits argument count
- Manages memory properly

**Key Operations**:
- Tokenizes input string
- Removes leading/trailing spaces
- Allocates memory for tokens
- Properly frees memory

## 5. Builtin Commands Check
**File**: `builtin_commands.c`
```c
int handle_builtin_commands(char **args, int num_args, char *input, char **env)
```
**Purpose**:
Handles internal commands:
- `exit`: Terminates shell
- `cd`: Changes directory
- `env`: Displays environment

**Key Operations**:
- Identifies builtin commands
- Routes to appropriate handler
- Manages command execution
- Returns execution status

## 6. Command Search
**File**: `path.c`
```c
char *get_file_path(char *command, char **env)
char *search_path(char *command, char *path)
char *check_current_dir(char *command)
```
**Purpose**:
- Searches command in PATH
- Verifies execution permissions
- Builds complete command path

**Key Operations**:
- Parses PATH environment variable
- Checks each directory
- Validates file permissions
- Constructs absolute paths

## 7. Command Execution
**File**: `exec.c`
```c
int execute_command(char *input, char *argv[], char **env, char *program_name)
void execute_child(char *cmd_path, char **args, char **env)
```
**Purpose**:
- Creates child process using `fork()`
- Executes command with `execve()`
- Waits for child process completion
- Handles return status

**Key Operations**:
- Process creation and management
- Command execution
- Status monitoring
- Resource cleanup

## 8. Error Handling
**File**: `print_error.c`
```c
void print_error(char *program_name, char *cmd, char *error_msg)
```
**Purpose**:
Error messages for:
- Command not found
- Permission denied
- Execution errors

**Key Operations**:
- Formats error messages
- Writes to STDERR
- Includes program context
- Provides meaningful feedback

## 9. Utility Functions
**File**: `utils.c`
```c
int _strlen(char *str)
char *_strdup(char *str)
char *_strcpy(char *dest, char *src)
char *_strchr(const char *s, int c)
char *_memset(char *s, char b, unsigned int n)
```
**Purpose**:
- String manipulation
- Memory management
- Helper functions

**Key Operations**:
- String length calculation
- Memory allocation/deallocation
- String copying and comparison
- Character operations

## 10. CD Management
**File**: `cd.c`
```c
void handle_cd(char **args, int num_args, char **env)
void update_oldpwd(const char *current_dir)
int save_current_dir(char *buf, size_t size)
```
**Purpose**:
Handles:
- Directory changes
- Special cases (cd -, cd ~)
- PWD/OLDPWD environment variables

**Key Operations**:
- Directory validation
- Path resolution
- Environment updates
- Error checking

## 11. Environment Management
**File**: `env.c`
```c
char *_getenv(const char *name, char **env)
void print_env(char **env)
```
**Purpose**:
- Access to environment variables
- Environment display
- Variable modification

**Key Operations**:
- Variable lookup
- Environment printing
- Value modification
- Memory management

## Execution Flow

1. Shell starts
2. Main loop:
   - Display prompt (if interactive)
   - Read user input
   - Parse command
   - Check for builtin command
   - If not builtin, search and execute command
   - Wait for completion
   - Return to start
3. Continue until `exit` or EOF

## Resource Management

- Proper memory deallocation
- File descriptor closure
- Child process cleanup
- Exit cleanup procedures

## Return Codes

- 0: Success
- 1: General error
- 127: Command not found
- 2: Syntax error

## Error Handling Strategy

1. **Input Validation**
   - Check for NULL pointers
   - Validate argument counts
   - Verify file permissions

2. **Memory Management**
   - Check allocation success
   - Free resources properly
   - Handle memory leaks

3. **Process Management**
   - Handle fork failures
   - Manage child processes
   - Clean up zombie processes

4. **Command Execution**
   - Validate command existence
   - Check execution permissions
   - Handle execution failures

## Best Practices

1. **Code Organization**
   - Modular function design
   - Clear file structure
   - Consistent error handling

2. **Memory Safety**
   - Proper allocation/deallocation
   - NULL checks
   - Boundary checking

3. **Error Handling**
   - Meaningful error messages
   - Proper error codes
   - Graceful failure handling

4. **Documentation**
   - Function descriptions
   - Parameter explanations
   - Return value clarification
