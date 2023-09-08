#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void display_prompt(void);
char *read_command(void);

int main(void) {
	while (1) {
		display_prompt();

		char *input = read_command();
		if (input == NULL) {
			printf("\n");
			break;
		}

		if (strlen(input) > 0) {
			pid_t pid = fork();

			if (pid == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			}

			if (pid == 0) {
				execlp(input, input, (char *)NULL);
				perror(input);
				exit(EXIT_FAILURE);
			} else {
				int status;
				wait(&status);

				if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
					printf("%s: No such file or directory\n", input);
				}
			}
		}

		free(input);
	}

	return (EXIT_SUCCESS);
}

void display_prompt(void) {
	printf("#cisfun$ ");
}

char *read_command(void) {
	char *input = NULL;
	size_t bufsize = 0;

	ssize_t read_chars = getline(&input, &bufsize, stdin);

	if (read_chars == -1) {
		if (feof(stdin)) {
			free(input);
			return NULL;
		} else {
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	if (input[read_chars - 1] == '\n') {
		input[read_chars - 1] = '\0';
	}

	return input;
}

