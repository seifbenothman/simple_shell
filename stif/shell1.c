#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * Function prototypes
 */
void display_prompt(void);
void remove_newline(char *str);
void run_shell(void);

int main(void) 
{
	run_shell();
	return (EXIT_SUCCESS);
}

void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

void remove_newline(char *str)
{
	int len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
	}
}

void run_shell(void) 
{
	char *input = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;
	char **args = NULL;
	pid_t pid;

	while (1) {
		display_prompt();
		characters_read = getline(&input, &bufsize, stdin);

		if (characters_read == -1) {
			break;
		}

		remove_newline(input);
		pid = fork();

		if (pid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		args = malloc(2 * sizeof(char *));
		if (args == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		args[0] = input;
		args[1] = NULL;

		if (pid == 0) {
			if (execve(input, args, NULL) == -1) {
				perror("execve");
				exit(EXIT_FAILURE);
			}
			free(args);
		} else {
			wait(NULL);
			free(args);
		}
	}

	if (input) {
		free(input);
	}
	exit(EXIT_SUCCESS);
}
