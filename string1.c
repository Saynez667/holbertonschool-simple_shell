#include "shell.h"

/**
 * _strlen - Calculate length of string
 * @s: String to measure
 * Return: Length of string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;
	return (len);
}

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 * Return: Integer less than, equal to, or greater than zero
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strdup - Duplicates a string
 * @str: String to duplicate
 * Return: Pointer to new string or NULL
 */
char *_strdup(const char *str)
{
	char *dup;
	int len, i;

	if (!str)
		return (NULL);

	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);

	for (i = 0; i <= len; i++)
		dup[i] = str[i];

	return (dup);
}