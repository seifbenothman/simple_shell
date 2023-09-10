#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * main - Simple shell program
 *
 * Return: Always 0.
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;
	info_t info;
	
	while (1)
	{
		printf("#cisfun$ ");
		characters_read = getline(&buffer, &bufsize, stdin);

		if (characters_read == -1)
		{
			printf("\n");
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		if (buffer[characters_read - 1] == '\n')
			buffer[characters_read - 1] = '\0';

		if (_strcmp(buffer, "exit") == 0)
		{
			int exit_status =my exit(&info);
			if (exit_status == -2)
			{
				printf("Exit with status: %d\n", info.err_num);
				free(buffer);
				exit(info.err_num);
			}
