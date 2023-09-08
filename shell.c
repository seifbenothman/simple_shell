#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
	char *input = NULL;
	size_t bufsize = 0;

	while (1) {
		printf("#cisfun$ ");

		ssize_t read_chars = getline(&input, &bufsize, stdin);

		if (read_chars == -1) {
			if (feof(stdin)) {
				printf("\n");
				break;
			} else {
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}

		if (input[read_chars - 1] == '\n') {
			input[read_chars - 1] = '\0';
		}

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
	return (EXIT_SUCCESS);
}
