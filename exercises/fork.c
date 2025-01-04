#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t pid;

    printf("Before fork\n");
    pid = fork();
    if (pid == -1)
    {
        perror("Error:");
        return (1);
    }
    printf("After fork\n");
    my_pid = getpid();
    printf("My pid is %u\n", my_pid);
    if (pid == 0)
    {
        printf("(%u) I am the child\n", my_pid);
    }
    else
    {
        printf("(%u) %u I am the parent\n", my_pid, pid);
    }
    return (0);
}
