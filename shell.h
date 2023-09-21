#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

extern char **environ;

/* Define your custom data structures here */
typedef struct
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
char *find_command_in_path(const char *command);
void execute_command_by_path(
		shell_data_t *shell_data, const char *command_path);

#endif /* MY_SHELL_H */
