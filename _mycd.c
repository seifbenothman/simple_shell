#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * _mycd - Change the current working directory.
 * @info: Pointer to info_t structure.
 *
 * This function changes the current working directory based on the provided path
 * or defaults to the user's home directory if no path is specified. It also updates
 * the PWD and OLDPWD environment variables accordingly.
 */
void _mycd(info_t *info)
{
	char *path = NULL;
	int chdir_ret;

	if(!path)
	{
		path = getenv("HOME");
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return;
		}
	}

	chdir_ret = chdir(path);

	if (chdir_ret == -1)
	{
		perror("cd");
	}
	else
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			setenv("PWD", cwd, 1);
			setenv("OLDPWD", info->cwd, 1);
		}
	}
}
