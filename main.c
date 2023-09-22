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
	return (NULL);
}

void findExecutable(char *command, char *exePath, char *pathVar) {
	char *path = getenv(pathVar);
	char *token;

	token = strtok(path, ":");

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
	int len = strlen(arg);
	int k;

	for (k = 0; k < len; k++) {
		if (strchr("\"'`\\*&#", arg[k])) {
			memmove(arg + k + 1, arg + k, len - k + 1);
			arg[k] = '\\';
			len++;
			k++;
		}
	}
}

void executeCommand(char *inputCmd, char *pathVar, int *commandCount) {
	char *args[MAX_ARG_SIZE];
	int argCount = 0;
	int j;

	char *token = strtok(inputCmd, " \t\n");
	pid_t pid;

	while (token != NULL && argCount < MAX_ARG_SIZE - 1) {
		args[argCount++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[argCount] = NULL;

	for (j = 0; j < argCount; j++) {
		handleSpecialChars(args[j]);
	}

	pid = fork();

	if (pid == -1) {
		perror("fork");
	} else if (pid == 0) {
		char exePath[50];

		findExecutable(args[0], exePath, pathVar);
		if (exePath[0] == '\0') {
			fprintf(stderr, "hsh: %d: %s: command not found\n", (*commandCount)++, args[0]);
			exit(1);
		}
		execvp(exePath, args);
		perror("./myShell");

		exit(1);
	} else {
		wait(NULL);
	}
}

int main() {
	char userInput[MAX_INPUT_SIZE];
	int commandCount = 1; /* Initialize commandCount to 1 for each shell session */

	while (1) {
		printf("$ ");
		if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
			break;
		}

		userInput[strcspn(userInput, "\n")] = '\0';

		if (strcmp(userInput, "exit") == 0) {
			break;
		}

		executeCommand(userInput, "PATH", &commandCount);
		commandCount++;
	}

	return (0);
}
