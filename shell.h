#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function prototypes */
int main(void);
char *custom_getline(void);

#endif /* SHELL_H */
