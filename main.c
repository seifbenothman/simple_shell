int main(void) {
	char *input = NULL;
	size_t bufsize = 0;

	while (1) {
		display_prompt();

		ssize_t read_chars = read_user_input(&input);

		if (read_chars == -1) {
			handle_error("Error reading input");
			continue;
		}

		remove_newline(input);

		pid_t pid = fork();

		if (pid == -1) {
			handle_error("Error forking");
			continue;
		}

		if (pid == 0) {
			char *token = strtok(input, " ");
			if (token) {
				execvp(token, &token);
				handle_error("Command not found");
				exit(EXIT_FAILURE);
			} else {
				exit(EXIT_SUCCESS);
			}
		} else {
			int status;
			wait(&status);
		}

		free(input);
	}

	return (EXIT_SUCCESS);
}
