#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * Function prototypes
 */
void initialize_info(info_t *info);
void run_shell(info_t *info);
void cleanup(info_t *info);

int main(void) 
{
	info_t info;
	initialize_info(&info);
	run_shell(&info);
	cleanup(&info);
	return (EXIT_SUCCESS);
}

void initialize_info(info_t *info) 
{
	info->cwd = NULL;
	info->err_num = 0;
}

void run_shell(info_t *info) 
{
	pid_t pid;
	char *input = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;
	int exit_status;

	while (1) {
		display_prompt();
		characters_read = getline(&input, &bufsize, stdin);

		if (characters_read == -1) {
			handle_error("Error reading input");
			continue;
		}

		remove_newline(input);

		printf("#cisfun$ ");
		characters_read = getline(&input, &bufsize, stdin);

		if (characters_read == -1) {
			printf("\n");
			free(input);
			exit(EXIT_SUCCESS);
		}

		if (input[characters_read - 1] == '\n') {
			input[characters_read - 1] = '\0';
		}

		if (strcmp(input, "exit") == 0) {
			exit_status = info->err_num;
			if (exit_status == -2) {
				printf("Exit with status: %d\n", info->err_num);
				free(input);
				exit(info->err_num);
			} else if (exit_status == 1) {
				continue;
			}
		} else if (strcmp(input, "cd") == 0) {
			_mycd(info);
			continue;
		}

		pid = fork();

		if (pid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		char **args = NULL;
		args = malloc(2 * sizeof(char *));
		if (args == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
		}
		args[0] = input;
		args[1] = NULL;
		}
		if (pid == 0) {
			if (execve(input, args, NULL) == -1) {
				perror("execve");
				exit(EXIT_FAILURE);
			}
		} else {
			wait(NULL);
		}
	}
}

void cleanup(info_t *info) 
{
	if (info->cwd)
	{
		free(info->cwd);
	}
}
