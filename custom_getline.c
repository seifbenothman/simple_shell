#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

#define READ_SIZE 1024

/**
 * custom_getline - Custom getline function.
 *
 * Return: A pointer to the line read, or NULL on failure or EOF.
 */
char *custom_getline(void) 
{
	static char buffer[READ_SIZE];
	static size_t buffer_size = 0;
	static size_t buffer_pos = 0;
	char *line = NULL;
	size_t line_size = 0;
	ssize_t bytes_read = 0;
	int found_newline = 0;

	while (1) 
	{
		if (buffer_pos == buffer_size) {
			bytes_read = read(STDIN_FILENO, buffer, READ_SIZE);
			if (bytes_read <= 0) {
				if (line_size > 0) {
					return (line);
				}
				return (NULL);
			}
			buffer_size = (size_t)bytes_read;
			buffer_pos = 0;
		}
		for (size_t i = buffer_pos; i < buffer_size; i++) {
			if (buffer[i] == '\n') {
				found_newline = 1;
				buffer[i] = '\0';
				line_size += i - buffer_pos + 1;
				buffer_pos = i + 1;
				break;
			}
		}
		if (found_newline)
		{
			break;
		}
		line = realloc(line, line_size + buffer_size - buffer_pos + 1);
		if (!line) 
		{
		return (NULL);
		}
		for (size_t i = buffer_pos; i < buffer_size; i++)
		{
			line[line_size++] = buffer[i];
		}
		buffer_pos = buffer_size;
	}

	return (line);
