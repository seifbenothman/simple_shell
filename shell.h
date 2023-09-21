#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
struct info_t;
extern char **environ;

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

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* Function prototypes for your custom functions */
void free_shell_data(shell_data_t *shell_data);
void initialize_shell_data(shell_data_t *shell_data, char **argv);
void handle_sigint(int signal);
void shell_loop(shell_data_t *shell_data);
char *my_strdup(const char *str);
char *convert_to_string(int num);
char *find_command_in_path(const char *command);
void execute_command_by_path(
		shell_data_t *shell_data, const char *command_path);

/* Function prototypes for the code you provided */
int _myenv(shell_data_t *shell_data);
char *_getenv(shell_data_t *shell_data, const char *name);
int _mysetenv(shell_data_t *shell_data);
int _myunsetenv(shell_data_t *shell_data);
int populate_env_list(shell_data_t *shell_data);

#endif /* SHELL_H */
