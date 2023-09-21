#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 1024

/**
 * execute_command - Execute a command entered by the user.
 * @command: The command to execute.
 * @env: Array of environment variables.
 *
 * This function should handle the execution logic for the shell.
 * You can use functions like fork(), execvp(), and wait() to execute commands.
 * For simplicity, let's just print the command for now.
 */

void execute_command(const char *command);
{
	pid_t child_pid = fork();
	if (child_pid == -1) 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0) 
	{
		char *args[MAX_INPUT_LENGTH];
		char *token;
		int arg_count = 0;

		token = strtok((char *)command, " ");
		while (token != NULL) 
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;
		if (waitpid(child_pid, &status, 0) == -1)
			perror("waitpid");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
	{
		printf("Command exited with status %d\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("Command terminated by signal %d\n", WTERMSIG(status));
	}
}

/**
 * main - Entry point of the simple shell program.
 * @argc: Number of command-line arguments (unused).
 * @argv: Array of command-line argument strings (unused).
 * @env: Array of environment variables.
 *
 * This function initializes the shell and enters a loop to read and execute commands.
 */
int main(int argc, char **argv, char **env) 
{
	char input[MAX_INPUT_LENGTH];
	int line_number = 1;

	while (1) 
	{
		size_t input_length;
		printf("$ ");
		if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) 
		{
			break;
		}
		input_length = strlen(input);
		if (input_length > 0 && input[input_length - 1] == '\n') 
		{
			input[input_length - 1] = '\0';
		}

		if (strcmp(input, "exit") == 0) 
		{
			break;
		}
		execute_command(input, env);
		line_number++;
	}

	return (0);
}
