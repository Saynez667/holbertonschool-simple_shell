# Create a Simple Shell
![Capture d'écran 2024-12-19 120554](https://github.com/user-attachments/assets/dacd684d-a94a-434f-b034-59449049617b)
## Table of Contents :

- [Project Overview](#Project-Overview)
- [Requirements](#Requirements)
- [Man Page](#Man-Page)
- [Flowchart](#Flowchart)
- [Documentation](#Documentation)
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
![Flowchart Simple Shell](https://github.com/user-attachments/assets/f30884c1-9ec7-4bff-9856-a78bd0dfb6e2)

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
## Documentation
For developers interested in understanding or modifying the code, we provide a comprehensive (In English) [Technical Documentation](DOCUMENTATION_EN.md) (Or in French) [Technical Documentation](DOCUMENTATION_FR.md) that includes:
- Detailed function descriptions
- Program flow explanation
- Error handling strategies
- Resource management
- Best practices

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
Header file containing all function prototypes and necessary includes for the shell program.
```
- **builtin_commands.c**
```
 Implements built-in shell commands like exit, env, and cd.
```
- **cd.c**
```
Implements the change directory (cd) command functionality.
```
- **env.c**

```
Functions for handling environment variables, including getting and printing them.
```
- **exec.c**

```
Contains functions for executing commands, including forking processes and handling command paths.
```
- **exit.c**
```
Functions for handling the exit command and exit status.
```
- **input.c**
```
Handles reading user input from the command line using getline.
```
- **path.c**
```
Handles finding command executables in the system PATH.
```
- **print_error.c**
```
Functions for printing error messages to stderr.
```
- **prompt.c**
```
Handles displaying the shell prompt.
```
- **shell.c**
```
Main function that runs the shell program. It displays the prompt, gets user input and processes commands.
```
- **tokenize.c**
```
Functions for splitting command lines into tokens/words.
```
- **utils.c**
```
Helper functions for string manipulation and memory management.
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
