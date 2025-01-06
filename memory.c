#include "shell.h"

/**
 * _realloc - Reallocates a memory block
 * @ptr: Pointer to previously allocated memory
 * @old_size: Size of allocated space for ptr
 * @new_size: New size of memory block
 *
 * Return: Pointer to reallocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (!ptr)
		return (malloc(new_size));

	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	for (i = 0; i < old_size && i < new_size; i++)
		*((char *)new_ptr + i) = *((char *)ptr + i);

	free(ptr);
	return (new_ptr);
}

/**
 * free_args - Frees array of strings
 * @args: Array to free
 *
 * Return: void
 */
void free_args(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}