#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

/* Define your custom data structures here */

/**
 * struct shell_data_t - Custom data structure for shell data.
 * @argv: An array of command-line arguments.
 * @input_buffer: A buffer for storing user input.
 * @args: An array of parsed command arguments.
 * @exit_status: The exit status of the shell.
 * @command_count: The count of executed commands.
 * @environment: An array of environment variables.
 * @process_id: The process ID of the shell.
 */
typedef struct shell_data_t
{
	char **argv;
	char *input_buffer;
	char **args;
	int exit_status;
	unsigned int command_count;
	char **environment;
	char *process_id;
}
shell_data_t;

/* Function prototypes */
void free_shell_data(shell_data_t *shell_data);
void initialize_shell_data(shell_data_t *shell_data, char **argv);
void handle_sigint(int signal);
void shell_loop(shell_data_t *shell_data);
char *my_strdup(const char *str);
char *convert_to_string(int num);
char *getEnvVar(const char *envVarName, shell_data_t *shell_data);
void findExecutable(const char *command, char *exePath, shell_data_t *shell_data);
void handleSpecialChars(char *arg);

#endif /* SHELL_H */
