#include "shell.h"

/**
 * _strlen - Calculate length of string
 * @str: String to measure
 * Return: Length of string
 */
int _strlen(char *str)
{
	int len = 0;

	if (!str)
		return (0);

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
	int len = 0;

	if (!str)
		return (NULL);

	len = _strlen(str);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	return (_strcpy(dup, str));
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

	if (!dest || !src)
		return (NULL);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _memset - Fills memory with a constant byte
 * @s: Memory area to fill
 * @b: Constant byte to fill with
 * @n: Number of bytes to fill
 * Return: Pointer to memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * _strchr - Locates a character in a string
 * @s: String to search
 * @c: Character to find
 * Return: Pointer to first occurrence of c in s, or NULL if not found
 */
char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
