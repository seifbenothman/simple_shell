#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char *find_command_in_path(const char *command)
{

	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		char *full_path = malloc(strlen(dir) + strlen(command) + 2);

		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

void execute_command_by_path(
		shell_data_t *shell_data, const char *command_path)
{
	if (execve(command_path, shell_data->args, shell_data->environment) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
