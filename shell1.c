#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

void display_prompt(void) 
{
	printf("#cisfun$ ");
	fflush(stdout);
}

void handle_error(const char *message)
{
	perror(message);
}

void remove_newline(char *str)
{
	int len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
	}
}

/**
 * main - Simple shell program
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;
	info_t info;
	int exit_status;
	pid_t pid;
	char *args[2];

	while (1)
	{
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			display_prompt();

			characters_read = getline(&input, &bufsize, stdin);

			if (characters_read == -1)
			{
				handle_error("Error reading input");
				continue;
			}

			remove_newline(input);
			printf("#cisfun$ ");
			characters_read = getline(&input, &bufsize, stdin);

			if (characters_read == -1)
			{
				printf("\n");
				free(input);
				exit(EXIT_SUCCESS);
			}

			if (input[characters_read - 1] == '\n')
				input[characters_read - 1] = '\0';

			if (strcmp(input, "exit") == 0)
			{
				exit_status = info.err_num;
				if (exit_status == -2)
				{
					printf("Exit with status: %d\n", info.err_num);
					free(input);
					exit(info.err_num);
				}
				else if (exit_status == 1)
					continue;
			}
			else if (strcmp(input, "cd") == 0)
			{
				_mycd(&info);
				continue;
			}

			args[0] = input;
			args[1] = NULL;

			if (execve(input, args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	return (EXIT_SUCCESS);
}
