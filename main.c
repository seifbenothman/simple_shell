#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 *main - Entry point for the simple shell.
 *
 *Return: Always 0.
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;
	int status;
	pid_t pid;

	while (1)
	{
		printf("$ ");

		characters_read = getline(&buffer, &bufsize, stdin);

		if (characters_read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				free(buffer);
				exit(EXIT_SUCCESS);
			}
			perror("getline");
			free(buffer);
			exit(EXIT_FAILURE);
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			free(buffer);
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			char *args[2];
			args[0] = buffer;
			args[1] = NULL;

			if (execvp(buffer, args) == -1)
			{
				perror("execvp");
				free(buffer);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
			{
				perror("wait");
				free(buffer);
				exit(EXIT_FAILURE);
			}
		}
	}

	free(buffer);
	return (EXIT_SUCCESS);
}

