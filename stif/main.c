#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int main(void) 
{
	char *input = NULL;
	size_t bufsize = 0;

	while (1) 
	{
		display_prompt();

		ssize_t read_chars = read_user_input(&input);

		if (read_chars == -1) 
		{
			handle_error("Error reading input");
			continue;
		}
		remove_newline(input);

		if (strcmp(input, "exit") == 0) 
		{
			free(input);
			break;
		}
		pid_t pid = fork();

		if (pid == -1) 
		{
			handle_error("Error forking");
			continue;
		}
		if (pid == 0) 
		{
			char *args[256];

			char *token = strtok(input, " ");
			int i = 0;

			while (token != NULL) 
			{
				args[i] = token;
				token = strtok(NULL, " ");
				i++;
			}
			args[i] = NULL;

			if (execvp(args[0], args) == -1) 
			{
				handle_error("Command not found");
				exit(EXIT_FAILURE);
			}
		} 
		else 
		{
			int status;
			wait(&status);
		}
		free(input);
	}
	return (EXIT_SUCCESS);
}
