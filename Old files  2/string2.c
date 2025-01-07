#include "shell.h"

/**
 * _atoi - Convert string to integer
 * @str: String to convert
 * Return: Integer value
 */
int _atoi(const char *str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	while (str[i] == ' ')
		i++;

	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') ? -1 : 1;
		i++;
	}

	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return (sign * result);
}

/**
 * _print_error - Print error message to stderr
 * @message: Error message
 * Return: void
 */
void _print_error(const char *message)
{
	write(STDERR_FILENO, message, _strlen(message));
}

/**
 * _strchr - Locates character in string
 * @s: String to search
 * @c: Character to find
 * Return: Pointer to character or NULL
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}