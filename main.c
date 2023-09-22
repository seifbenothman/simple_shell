#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

int main(int argc, char **argv, char **env)
{
	char userInput[MAX_INPUT_SIZE];
	int commandCount = 1;

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

		executeCommand(userInput, "PATH", &commandCount, env);
		commandCount++;
	}

	return (0);
}
