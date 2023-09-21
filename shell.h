#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_INPUT_LENGTH 1024

void execute(char *command, char **env, int line_number);
void execute_command(const char *command);

#endif /* SHELL_H */
