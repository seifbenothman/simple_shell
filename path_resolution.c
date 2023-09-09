#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int resolve_command(const char *command, char **resolved_path, char **envp) {
	char *path_env = _getenv(envp, "PATH");

	if (!path_env) {
		return -1;
	}

	char *token = strtok(path_env, ":");

	while (token) {
		char full_path[1024];
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);

		if (access(full_path, F_OK) == 0) {
			*resolved_path = strdup(full_path);

			if (!*resolved_path) {
				return -1;
			}

			return 1;
		}

		token = strtok(NULL, ":");
	}

	return 0;
}

