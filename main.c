#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

void parseInputCommand(char *inputCmd, char *args[], int *argCount) {
	char *token = strtok(inputCmd, " \t\n");

	*argCount = 0;
	while (token != NULL && *argCount < MAX_ARG_SIZE - 1) {
		args[(*argCount)++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	args[*argCount] = NULL;
}

void runCommand(char *args[], char *pathVar, int *commandCount, char **env) {
	pid_t pid;
	int argCount = *commandCount;

	handleSpecialChars(args[0]);

	pid = fork();

	if (pid == -1) {
		perror("fork");
	} else if (pid == 0) {
		char exePath[MAX_INPUT_SIZE];

		findExecutable(args[0], exePath, pathVar);
		if (exePath[0] == '\0') {
			fprintf(stderr, "hsh: %d: %s: command not found\n", argCount, args[0]);
			exit(1);
		}
		execve(exePath, args, env);
		perror("execve");
		exit(1);
	} else {
		wait(NULL);
	}
}

int main(int argc, char **argv, char **env) {
	char userInput[MAX_INPUT_SIZE];
	int commandCount = 1;

	(void)argc;
	(void)argv;

	while (1) {
		printf("$ ");
		if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
			break;
		}

		userInput[strcspn(userInput, "\n")] = '\0';

		if (strcmp(userInput, "exit") == 0) {
			break;
		}

		char *args[MAX_ARG_SIZE];
		int argCount;

		parseInputCommand(userInput, args, &argCount);
		runCommand(args, "PATH", &commandCount, env);

		commandCount++;
	}

	return (0);
}
