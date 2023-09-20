#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *get_env(char *env_var, char **env);
void add_path(char *a, char *exe, char **env);
void handle_special(char *arg);
void execute(char *command, char **env, int line_number);

#endif /* SHELL_H */
