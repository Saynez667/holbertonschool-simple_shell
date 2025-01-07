#include "shell.h"

/**
 * _strlen - Calculate length of string
 * @str: String to measure
 * Return: Length of string
 */
int _strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}

/**
 * _strdup - Duplicates a string
 * @str: String to duplicate
 * Return: Pointer to new string
 */
char *_strdup(char *str)
{
	char *dup;
	int i, len = 0;

	if (!str)
		return (NULL);

	while (str[len])
		len++;

	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	for (i = 0; str[i]; i++)
		dup[i] = str[i];
	dup[i] = '\0';

	return (dup);
}

/**
 * _strcpy - Copies a string
 * @dest: Destination buffer
 * @src: Source string
 * Return: Pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}