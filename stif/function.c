#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

/**
 *  Get the value of an environment variable.
 *
 *  Parameters:
 *  envVarName: The name of the environment variable to retrieve.
 *  env: The array of environment variables.
 *
 *  Returns:
 *  The value of the environment variable, or NULL if not found.
 */
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

/** 
 * Find the executable path for a given command.
 *
 * command: The command to search for.
 * exePath: A buffer to store the executable path.
 * pathVar: The name of the PATH environment variable.
 */
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

/**
 * Handle special characters in a command argument.
 *
 * arg: The argument string to process.
 */
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

/**
 * Free memory allocated for command arguments.
 *
 * args: An array of command arguments.
 * argCount: The number of arguments in the array.
 */
void freeArgs(char *args[], int argCount)
{
	int j;

	for (j = 0; j < argCount; j++)
	{
		free(args[j]);
	}
}
