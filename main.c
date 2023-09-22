#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

char *getEnvVar(char *envVarName, char **env) {
	int i = 0;
	char *key;

	while (env[i]) {
		key = strtok(env[i], "=");
		if (strcmp(envVarName, key) == 0) {
			return strtok(NULL, "\n");
		}
		i++;
	}
	return NULL;
}

void findExecutable(char *command, char *exePath, char *pathVar) {
	char *path = getenv(pathVar);
	char *token;
	char tempPath[MAX_INPUT_SIZE];

	strcpy(tempPath, path);
	token = strtok(tempPath, ":");

	while (token != NULL) {
		strcpy(exePath, token);
		strcat(exePath, "/");
		strcat(exePath, command);

		if (access(exePath, X_OK) == 0) {
			return;
		}

		token = strtok(NULL, ":");
	}

	exePath[0] = '\0';
}

void handleSpecialChars(char *arg) {
	char *specialChars = "\"'`\\*&#";
	char *escapedArg = malloc(strlen(arg) * 2 + 1);
	int i, j = 0;

	if (escapedArg == NULL) {
		perror("malloc");
		exit(1);
	}

	for (i = 0; arg[i]; i++) {
		if (strchr(specialChars, arg[i])) {
			escapedArg[j++] = '\\';
		}
		escapedArg[j++] = arg[i];
	}

	escapedArg[j] = '\0';
	strcpy(arg, escapedArg);
	free(escapedArg);
}

void freeArgs(char *args[], int argCount) {
	int j;

	for (j = 0; j < argCount; j++) {
		free(args[j]);
	}
}

void executeCommand(char *inputCmd, char *pathVar, int *commandCount, char **env) {
	char *args[MAX_ARG_SIZE];
	int argCount = 0;

	char *token = strtok(inputCmd, " \t\n");
	pid_t pid;

	while (token != NULL && argCount < MAX_ARG_SIZE - 1) {
		args[argCount] = malloc(strlen(token) + 1);

		if (args[argCount] == NULL) {
			perror("malloc");
			exit(1);
		}
		strcpy(args[argCount], token);
		handleSpecialChars(args[argCount]);
		argCount++;
		token = strtok(NULL, " \t\n");
	}
	args[argCount] = NULL;

	pid = fork();

	if (pid == -1) {
		perror("fork");
		freeArgs(args, argCount);
	} else if (pid == 0) {
		char exePath[MAX_INPUT_SIZE];

		findExecutable(args[0], exePath, pathVar);
		if (exePath[0] == '\0') {
			fprintf(stderr, "hsh: %d: %s: command not found\n", (*commandCount)++, args[0]);
			freeArgs(args, argCount);
			exit(1);
		}
		execve(exePath, args, env);
		perror("execve");

		freeArgs(args, argCount);
		exit(1);
	} else {
		wait(NULL);
		freeArgs(args, argCount);
	}
}

int main(int argc, char **argv, char **env) {
	char *userInput = NULL;
	size_t inputSize = 0;
	int commandCount = 1;

	(void)argc;
	(void)argv;

	printf("$ ");
	getline(&userInput, &inputSize, stdin);
	while (userInput) {

		if (strcmp(userInput, "exit\n") == 0)
			break;

		if (userInput[0] == '\n') {
			userInput[0] = '\0';
		}

		if (strcmp(userInput, "exit") == 0) {
			break;
		}

		executeCommand(userInput, "PATH", &commandCount, env);
		commandCount++;

		userInput = NULL;
		free(userInput);

		printf("$ ");
		getline(&userInput, &inputSize, stdin);
	}

	free(userInput);

	return 0;
}
