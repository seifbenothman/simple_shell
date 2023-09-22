#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

char *getEnvVar(char *envVarName, char **env)
{
	int i = 0;
	char *key;

	while (env[i])
	{
		key = strtok(env[i], "=");
		if (strcmp(envVarName, key) == 0)
		{
			return (strtok(NULL, "\n"));
		}
		i++;
	}
	return (NULL);
}

void findExecutable(char *command, char *exePath, char *pathVar)
{
	char *path = getenv(pathVar);
	char *token;
	char tempPath[MAX_INPUT_SIZE];

	strcpy(tempPath, path);
	token = strtok(tempPath, ":");

	while (token != NULL)
	{
		strcpy(exePath, token);
		strcat(exePath, "/");
		strcat(exePath, command);

		if (access(exePath, X_OK) == 0)
		{
			return;
		}

		token = strtok(NULL, ":");
	}

	exePath[0] = '\0';
}

void handleSpecialChars(char *arg)
{
	int len = strlen(arg);
	int k;

	for (k = 0; k < len; k++)
	{
		if (strchr("\"'`\\*&#", arg[k]))
		{
			memmove(arg + k + 1, arg + k, len - k + 1);
			arg[k] = '\\';
			len++;
			k++;
		}
	}
}

void freeArgs(char *args[], int argCount)
{
	int j;

	for (j = 0; j < argCount; j++)
	{
		free(args[j]);
	}
}
