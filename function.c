#include "main.h"

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
	int lenth = strlen(arg);
	int F;

	for (F = 0; F < lenth; F++)
	{
		if (strchr("\"'`\\*&#", arg[F]))
		{
			memmove(arg + F + 1, arg + F, lenth - F + 1);
			arg[F] = '\\';
			lenth++;
			F++;
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

void executeCommand(char *inputCmd, char *pathVar, int *commandCount, char **env)
{
	char *args[MAX_ARG_SIZE];
	int argCount = 0;
	int j;

	char *token = strtok(inputCmd, " \t\n");
	pid_t pid;

	while (token != NULL && argCount < MAX_ARG_SIZE - 1)
	{
		args[argCount++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	args[argCount] = NULL;

	for (j = 0; j < argCount; j++)
	{
		handleSpecialChars(args[j]);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		freeArgs(args, argCount);
	}
	else if (pid == 0)
	{
		char exePath[MAX_INPUT_SIZE];

		findExecutable(args[0], exePath, pathVar);
		if (exePath[0] == '\0')
		{
			fprintf(stderr, "hsh: %d: %s: command not found\n", (*commandCount)++, args[0]);
			freeArgs(args, argCount);
			exit(1);
		}
		execve(exePath, args, env);
		perror("execve");

		freeArgs(args, argCount);
		exit(1);
	}
	else
	{
		wait(NULL);

		freeArgs(args, argCount);
	}
}
