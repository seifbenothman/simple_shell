#include "main.h"

int main(int argc, char **argv, char **env) {
	char *userInput = NULL;
	size_t inputSize = 0;
	int commandCount = 1;

	(void)argc;
	(void)argv;

	printf("$ ");
	getline(&userInput, &inputSize, stdin);
	while (userInput) {

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
