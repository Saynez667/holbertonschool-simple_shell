#include "shell.h"

#define READ_SIZE 1024

/**
 * _realloc_buffer - Reallocates memory for the line buffer
 * @line: The current line buffer
 * @old_size: Current size of the buffer
 * @new_size: New size to allocate
 *
 * Return: Pointer to newly allocated buffer, or NULL on failure
 */
static char *_realloc_buffer(char *line, size_t old_size, size_t new_size)
{
	char *new_line;
	size_t i;

	new_line = malloc(new_size);
	if (!new_line)
		return (NULL);

	for (i = 0; i < old_size && i < new_size; i++)
		new_line[i] = line[i];

	free(line);
	return (new_line);
}

/**
 * _process_buffer - Process the buffer for newline and update line
 * @buffer: Read buffer
 * @bytes_read: Number of bytes read
 * @line: Current line being built
 * @line_size: Current size of line
 * @total_read: Total bytes read for current line
 *
 * Return: Index where processing stopped, or -1 on failure
 */
static ssize_t _process_buffer(char *buffer, ssize_t bytes_read,
							 char **line, size_t *line_size, size_t *total_read)
{
	size_t i;
	size_t new_size;

	for (i = 0; i < (size_t)bytes_read; i++)
	{
		if (*total_read >= *line_size - 1)
		{
			new_size = *line_size * 2;
			*line = _realloc_buffer(*line, *line_size, new_size);
			if (!*line)
				return (-1);
			*line_size = new_size;
		}
		(*line)[*total_read] = buffer[i];
		(*total_read)++;

		if (buffer[i] == '\n')
			return (i + 1);
	}
	return (0);
}

/**
 * custom_getline - Reads a line from a file descriptor
 * @lineptr: Pointer to the buffer that will store the line
 * @n: Pointer to the size of the buffer
 * @fd: File descriptor to read from
 *
 * Return: Number of bytes read, -1 on failure
 */
ssize_t custom_getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[READ_SIZE];
	static size_t buffer_pos;
	static ssize_t bytes_in_buffer;
	size_t total_read = 0, line_size;
	ssize_t process_result;

	if (!lineptr || !n)
		return (-1);

	if (!*lineptr)
	{
		line_size = READ_SIZE;
		*lineptr = malloc(line_size);
		if (!*lineptr)
			return (-1);
		*n = line_size;
	}
	else
		line_size = *n;

	while (1)
	{
		if (buffer_pos >= (size_t)bytes_in_buffer)
		{
			bytes_in_buffer = read(fd, buffer, READ_SIZE);
			if (bytes_in_buffer <= 0)
			{
				if (total_read == 0)
					return (-1);
				break;
			}
			buffer_pos = 0;
		}

		process_result = _process_buffer(buffer + buffer_pos,
									   bytes_in_buffer - buffer_pos,
									   lineptr, &line_size, &total_read);
		if (process_result == -1)
			return (-1);
		
		if (process_result > 0)
		{
			buffer_pos += process_result;
			break;
		}
		
		buffer_pos = bytes_in_buffer;
	}

	(*lineptr)[total_read] = '\0';
	*n = line_size;
	return (total_read);
}
