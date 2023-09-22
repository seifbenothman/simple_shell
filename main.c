#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

/* Parse the user input command into arguments.
 *
 * inputCmd: The user input command string.
 * args: An array to store the parsed arguments.
 * argCount: A pointer to an integer to store the number of arguments.
 */
void parseInputCommand(char *inputCmd, char *args[], int *argCount)
{
	char *token = strtok(inputCmd, " \t\n");

	*argCount = 0;
	while (token != NULL && *argCount < MAX_ARG_SIZE - 1)
	{
		args[(*argCount)++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	args[*argCount] = NULL;
}

/* Run a command with its arguments.
 *
 * args: An array of command arguments.
 * pathVar: The name of the PATH environment variable.
 * commandCount: A pointer to an integer representing the command count.
 * env: The array of environment variables.
 */
void runCommand(char *args[], char *pathVar, int *commandCount, char **env)
{
	pid_t pid;
	int argCount = *commandCount;

	handleSpecialChars(args[0]);

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		char exePath[MAX_INPUT_SIZE];

		findExecutable(args[0], exePath, pathVar);
		if (exePath[0] == '\0')
		{
			fprintf(stderr, "hsh: %d: %s: command not found\n", argCount, args[0]);
			exit(1);
		}
		execve(exePath, args, env);
		perror("execve");
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}

/* Main function for the shell.
 *
 * argc: The number of command-line arguments.
 * argv: An array of command-line argument strings.
 * env: The array of environment variables.
 * Returns 0 on successful execution.
 */
int main(int argc, char **argv, char **env)
{
	char userInput[MAX_INPUT_SIZE];
	int commandCount = 1;
	char *args[MAX_ARG_SIZE];
	int argCount;

	(void)argc;
	(void)argv;

	while (1)
	{
		printf("$ ");
		if (fgets(userInput, sizeof(userInput), stdin) == NULL)
		{
			break;
		}

		userInput[strcspn(userInput, "\n")] = '\0';

		if (strcmp(userInput, "exit") == 0)
		{
			break;
		}

		parseInputCommand(userInput, args, &argCount);
		runCommand(args, "PATH", &commandCount, env);

		commandCount++;
	}

	return (0);
}
