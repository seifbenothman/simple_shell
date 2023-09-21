#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * find_command_in_path - Find a command in the directories listed in the PATH.
 *
 * @command: The command to search for.
 *
 * Return: A pointer to the full path of the command if found, or NULL
 */
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

/**
 * execute_command_by_path - Execute a command by its full path.
 *
 * @shell_data: The shell data structure.
 * @command_path: The full path of the command to execute.
 */
void execute_command_by_path(
		shell_data_t *shell_data, const char *command_path)
{
	if (execve(command_path, shell_data->args, shell_data->environment) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
