#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "shell.h"


/**
 * free_shell_data - Free memory allocated for shell data structure
 *
 * @shell_data: Shell data structure
 * Return: No return value
 */
void free_shell_data(shell_data_t *shell_data)
{
	unsigned int i;

	for (i = 0; shell_data->environment[i]; i++)
	{
		free(shell_data->environment[i]);
	}

	free(shell_data->environment);
	free(shell_data->process_id);
}

/**
 * initialize_shell_data - Initialize shell data structure
 *
 * @shell_data: Shell data structure
 * @argv: Argument vector
 * Return: No return value
 */
void initialize_shell_data(shell_data_t *shell_data, char **argv)
{
	unsigned int i;

	shell_data->argv = argv;
	shell_data->input_buffer = NULL;
	shell_data->args = NULL;
	shell_data->exit_status = 0;
	shell_data->command_count = 1;

	for (i = 0; environ[i]; i++)
	{
/* Calculate the number of environment variables */
	}

	shell_data->environment = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		shell_data->environment[i] = my_strdup(environ[i]);
	}

	shell_data->environment[i] = NULL;
	shell_data->process_id = convert_to_string(getpid());
}

/**
 * main - Entry point for the custom shell
 *
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success.
 */

int main(int argc, char **argv)
{
	shell_data_t shell_data;
	(void)argc;

	signal(SIGINT, handle_sigint);
	initialize_shell_data(&shell_data, argv);
	shell_loop(&shell_data);
	free_shell_data(&shell_data);

	if (shell_data.exit_status < 0)
		return (255);

	return (shell_data.exit_status);
}
