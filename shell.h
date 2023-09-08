#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 *Display the shell prompt.
 */
void display_prompt(void);
void display_prompt(void);
ssize_t read_user_input(char **input);
void handle_command(const char *command);
void handle_error(const char *message);
void remove_newline(char *str);

/**
 *Read a command from the user.
 * 
 *@return A dynamically allocated string containing the user's input.
 *         NULL is returned on EOF (Ctrl+D).
 */
char *read_command(void);

#endif /* _SHELL_H_ */
