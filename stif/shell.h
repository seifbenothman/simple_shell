#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

void parseInputCommand(char *inputCmd, char *args[], int *argCount);
void runCommand(char *args[], char *pathVar, int *commandCount, char **env);
char *getEnvVar(char *envVarName, char **env);
void findExecutable(char *command, char *exePath, char *pathVar);
void handleSpecialChars(char *arg);
void freeArgs(char *args[], int argCount);

#endif /* SHELL_H */
