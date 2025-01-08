# Create a Simple Shell
![Capture d'écran 2024-12-19 120554](https://github.com/user-attachments/assets/dacd684d-a94a-434f-b034-59449049617b)
## Table of Contents :

- [Project Overview](#Project-Overview)
- [Requirements](#Requirements)
  [Man Page](#Man-Page)
- [Flowchart](#Flowchart)
- [Usage](#Usage)
- [Installation & Compilation](#Installation-&-Compilation)
- [Mandatory Tasks](#Mandatory-Tasks)
- [File description](#File-description)
- [Examples and Tests](#Examples-and-Tests)
- [Authors](#Authors)

## Project Overview

This project consists of creating a simple shell in C, gradually implementing the essential functionalities of a UNIX command interpreter. 

## Requirements

**1. Allowed Editors :** You can use 'Vi', 'Vim' or 'Emacs'.

**2. Operating System :** All your files will be compiled on Ubuntu 20.04 LTS.

**3. Coding Style :** This code use Betty Style for consistent and readable code. It will be checked using betty-style.pl and betty-doc.pl.

**4. File Ending :** All the source code files (.c files) end with a newline character (\n).

**5. Variables :** Avoid using global variables. Use local variables.

**6. Functions limits :** Limit the number of functions within each source code file to five or less.

**7. Header :** Include the "main.h" header file in all .c files to access necessary declarations and definitions with the prototypes.

**8. Authorized functions and macros :**

- all functions from string.h
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- printf (man 3 printf)
- fprintf (man 3 fprintf)
- vfprintf (man 3 vfprintf)
- sprintf (man 3 sprintf)
- putchar (man 3 putchar)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)
## Man Page

The man page is a file wich explains in detail how the function works. If you want see a full explanation of this function you can run our man page this way:
```
$ man ./man_page
```

## Flowchart
![flowchart simple shell ](https://github.com/user-attachments/assets/4b68c697-6787-46dd-b26d-001a1ebf7836)
## Usage

This will create a compilation file. You can run the shell in your terminal by using this command :

1. Clone this repository on your local machine :

```bash
git clone https://github.com/Saynez667/holbertonschool-simple_shell
```

2. To compile the program, this command has to be executed :
```bash
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
3. This will create a compilation file. You can run the shell in your terminal by using this command :
```bash
$ ./hsh
```
```bash
#user$ ls
#user$ /bin/ls
#user$ exit
## Installation & Compilation
## Mandatory Tasks
```

### Task 0 :
- Write a `README`
and write a `man` for your shell.
You should have an `AUTHORS` file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker.

### Task 1 :

- Write a beautiful code that passes the Betty checks

### Task 2 :

- Write a UNIX command line interpreter.

**Your Shell should:**

- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- You have to handle the “end of file” condition (Ctrl+D)

**You don’t have to:** 

- use the PATH
- implement built-ins
- handle special characters : `"`, `'`,``, `\`, `*`, `&`, `#`
- be able to move the cursor
- handle commands with arguments

**execve will be the core part of your Shell, don’t forget to pass the environ to it…**
```bash
julien@ubuntu:~/shell$ ./shell 
#cisfun$ ls
./shell: No such file or directory
#cisfun$ /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
#cisfun$ ^[[D^[[D^[[D
./shell: No such file or directory
#cisfun$ ^[[C^[[C^[[C^[[C
./shell: No such file or directory
#cisfun$ exit
./shell: No such file or directory
#cisfun$ ^C
julien@ubuntu:~/shell$ echo "/bin/ls" | ./shell
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
julien@ubuntu:~/shell$
```
## Task 3
**Simple shell 0.1 +**
- Handle command lines with arguments
## Task 4
**Simple shell 0.2 +**

- Handle the PATH
- fork must not be called if the command doesn’t exist
```bash
julien@ubuntu:~/shell$ ./shell_0.3
:) /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls -l /tmp 
total 20
-rw------- 1 julien julien    0 Dec  5 12:09 config-err-aAMZrR
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-colord.service-V7DUzr
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-rtkit-daemon.service-ANGvoV
drwx------ 3 root   root   4096 Dec  5 12:07 systemd-private-062a0eca7f2a44349733e78cb4abdff4-systemd-timesyncd.service-CdXUtH
-rw-rw-r-- 1 julien julien    0 Dec  5 12:09 unity_support_test.0
:) ^C
julien@ubuntu:~/shell$ 
```
## Task 5
**Simple shell 0.3 +**

- Implement the exit built-in, that exits the shell
- Usage: `exit`
- You don’t have to handle any argument to the built-in exit
## Task 6
**Simple shell 0.4 +**
```bash
Implement the env built-in, that prints the current environment
julien@ubuntu:~/shell$ ./simple_shell
$ env
USER=julien
LANGUAGE=en_US
SESSION=ubuntu
COMPIZ_CONFIG_PROFILE=ubuntu
SHLVL=1
HOME=/home/julien
C_IS=Fun_:)
DESKTOP_SESSION=ubuntu
LOGNAME=julien
TERM=xterm-256color
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DISPLAY=:0
$ exit
julien@ubuntu:~/shell$ 
```

## File description
- **shell.h**
```
This file is a header for a C shell program. It contains:
1-Standard library inclusions necessary for the shell to work.
2-Function declarations for:
Executing commands (eg: execute_command, read_input)
String manipulation (eg: _strlen, _strdup)
Management of built-in commands (eg: handle_builtin_commands, handle_cd)**
3-Its role is to define the shell interface, allowing other project files to access declared functions by simply including it
```
- **builtin_commands.c**
```
This file implements the shell's built-in command handling. The main handle_builtin_commands function:
1-Takes as input the command arguments, their number, the complete command, and environment variables.
2-Checks if the command is one of the following:
"exit": calls shell_exit to exit the shell
"cd": calls handle_cd to change directory
"env": calls print_env to display environment variables
3-Returns 1 if a built-in command has been processed, 0 otherwise.
```
- **cd.c**
```
This file implements the functionality of the shell's "cd" (change directory) command. The handle_cd function:
1-Handles three main cases:
"cd" without argument or "cd ~": changes to the home directory
"cd -": changes to the previous directory
"cd [path]": changes to the specified path
2-Use getenv to get HOME and OLDPWD environment variables
3-Use chdir to perform directory change
4-Handle errors with perror on failure
```
- **env.c**

```
This file implements the functionality to display the shell's environment variables. The print_env function:
1-Takes as input an array of strings representing the environment variables.
2-Iterates through each environment variable in the array.
3-For each variable:
Calculates the length of the string
Uses write to display the variable followed by a newline
4-Uses write instead of printf, likely for performance reasons or more precise output control.
```
- **exec.c**

```
This file implements the core command execution logic for the shell. It contains three main functions:
1-execute_child:
Executes the command in the child process using execve
Handles errors and exits if execution fails
2-handle_command_path:
Resolves the full path of the command
Handles both absolute/relative paths and commands in PATH
3-execute_command:
Main function for command execution
Tokenizes the input
Checks for built-in commands
Resolves the command path
Creates a child process using fork
Executes the command in the child process
Waits for the child process to complete in the parent process
```
- **exit.c**
```
This file implements the exit functionality for the shell. It contains two main functions:
1-handle_exit:
Frees the input memory
Exits the shell with the given status
2-shell_exit:
Handles the 'exit' command with or without an argument
If an argument is provided:
Checks if it's a valid number
Converts the string argument to an integer exit status
Calls handle_exit with the appropriate status
Returns 1 to indicate the command was handled
```
- **input.c**
```
This file implements the input reading functionality for the shell. The read_input function:
1-Uses getline to read user input from stdin
2-Dynamically allocates memory for the input buffer
3-Handles EOF (Ctrl+D) by freeing the buffer and exiting the program
4-Returns the input as a string
Key points:
Allows for variable-length input
Automatically handles memory allocation
Gracefully handles end-of-file condition
```
- **path.c**
```
This file implements utility functions for handling file paths in the shell. It contains two main functions:
1-concat_path:
Concatenates a directory path and a command name
Handles cases where the directory path doesn't end with a '/'
Returns the full path or NULL on failure
get_file_path:
2-Finds the full path of a command in the system
Checks if the command exists in the current directory
Searches for the command in directories listed in the PATH environment variable
Uses concat_path to build full paths for testing
Returns the full path of the command if found, or NULL if not found
Key points:
Handles memory allocation and deallocation
Uses custom string functions (_strlen, _strcpy, _strdup)
Utilizes system calls (stat, access) to check file existence and permissi
```
- **print_error.c**
```
This file implements an error reporting utility for the shell. The print_error function:
1-Takes three parameters:
program: The name of the shell program
cmd: The command that caused the error
msg: The error message to display
2-Writes the error message to stderr (file descriptor 2) in the format:
"[program]: 1: [cmd]: [msg]"
3-Uses write system call instead of printf, likely for more direct control over output
Key points:
Formats error messages consistently
Writes directly to stderr
Uses loops to write each character, ensuring full message is output
```
- **prompt.c**
```
This file implements the prompt functionality for the shell. The print_prompt function:
1-Checks if the input is coming from a terminal (interactive mode) using isatty()
2-If in interactive mode, it writes the prompt "ValakShell$ " to the standard output
Key points:
Uses isatty() to determine if the shell is running in interactive mode
Uses write() system call to output the prompt
Only displays the prompt in interactive mode, not when processing scripts or piped input
```
- **shell.c**
```
This file implements the main entry point and control loop for the shell. The main function:
1-Runs an infinite loop to continuously accept and process commands
2-Calls print_prompt() to display the shell prompt
3-Uses read_input() to get user input
4-Handles EOF (Ctrl+D) by exiting the shell
5-Calls execute_command() to process and execute the input
6-Frees the input buffer after each command execution
```
- **tokenize.c**
```
This file implements the input tokenization functionality for the shell. The tokenize_input function:
1-Takes two parameters:
input: The raw input string from the user
args: An array to store the tokenized arguments
2-Uses strtok to split the input string into tokens
Delimiters are space, tab, and newline characters
3-Stores each token in the args array
4-Terminates the args array with a NULL pointer
5-Returns the number of tokens (arguments) found
```
- **utils.c**
```
This file implements custom string manipulation functions for the shell. It contains three main functions:
1-_strlen:
Calculates the length of a string
Returns the number of characters in the string (excluding null terminator)
2-_strdup:
Creates a duplicate of a given string
Allocates new memory for the duplicate
Returns a pointer to the new string or NULL if memory allocation fails
3-_strcpy:
Copies a source string to a destination buffer
Ensures null-termination of the destination string
Returns a pointer to the destination string
```
## Examples and Tests

**Your shell should work like this in interactive mode:**
```bash
user@ubuntu:/# ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
user@ubuntu:/#
```
**But also in non-interactive mode:**
```bash
user@ubuntu:/# echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
user@ubuntu:/# cat test_ls_2
/bin/ls
/bin/ls
user@ubuntu:/# cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
user@ubuntu:/#
```
## Authors
[Saynez667](https://github.com/Saynez667)    
[Valak74200](https://github.com/valak74200)
