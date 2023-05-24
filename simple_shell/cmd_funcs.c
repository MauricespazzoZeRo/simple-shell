#include "main.h"

char *exit_cmd(const char* cmd, ...)
{
	va_list stts;
	int status;
	va_start(stts, cmd);

	char* exit;
	char* result = NULL;

	if (cmd != NULL)
	{
		status = va_arg(stts, int);
		va_end(stts);

		exit(status);
	}
}

char *env_cmd(const char* cmd)
{
	extern char **environ;	/* Access the global environ variable */

	/* Iterate over each environment variable and write them to stdout */
	char **env = environ;
	size_t len;

	while (*env != NULL)
	{
		len = _strlen(*env);
		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}

	return NULL;
}

char *setenv_cmd(const char *cmd, ...)
{
	va_list args;
	const char *name;
	const char *value;
	int overwrite;
	int result;

	/* Parse variable arguments */
	va_start(args, cmd);
	name = va_arg(args, const char *);
	value = va_arg(args, const char *);
	overwrite = va_arg(args, int);
	va_end(args);

	/* Call setenv to set the environment variable */
	result = setenv(name, value, overwrite);
	if (result != 0)
	{
		perror("setenv");
		return (NULL);
	}

	return (NULL);	/* Return NULL as no command output is expected */
}


char *unsetenv_cmd(const char *cmd, ...)
{
	va_list args;
	const char *name;
	int result;

	// Parse variable arguments
	va_start(args, cmd);
	name = va_arg(args, const char *);
	va_end(args);

	// Call unsetenv to remove the environment variable
	result = unsetenv(name);
	if (result != 0)
	{
		perror("unsetenv");
		return (NULL);
	}

	return (NULL);	/* Return NULL as no command output is expected */
}


char *cd_cmd(const char* cmd, ...)
{
	va_list args;
	const char *dir;
	char target_dir[256];
	const char *home_dir;
	const char *old_dir;
	char current_dir[256];
	char pwd_value[256];
	char *pwd_var;
	char *pwd_entry;

	/* Parse variable arguments */
	va_start(args, cmd);
	dir = va_arg(args, const char *);
	va_end(args);

	/* Determine the target directory */
	if (dir == NULL || strcmp(dir, "") == 0)
	{
		/* If no argument or an empty argument is given, use $HOME */
		home_dir = _getenv("HOME");
		if (home_dir == NULL)
		{
			perror("cd");
			return (NULL);
		}
		_strncpy(target_dir, home_dir, 256);
	}
	else if (strcmp(dir, "-") == 0)
	{
	/* If the argument is "-", change to the previous directory (stored in $OLDPWD) */
		old_dir = _getenv("OLDPWD");
		if (old_dir == NULL)
		{
			perror("cd");
			return (NULL);
		}
		strncpy(target_dir, old_dir, 256);
	}
	else
	{
		/* Use the provided directory argument */
		strncpy(target_dir, dir, 256);
	}

	/* Save the current working directory to $OLDPWD */
	if (getcwd(current_dir, 256) == NULL)
	{
		perror("cd");
		return (NULL);
	}
	if (setenv("OLDPWD", current_dir, 1) == -1)
	{
		perror("cd");
		return (NULL);
	}

	/* Change the current working directory */
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (NULL);
	}

	/* Update the environment variable PWD */
	pwd_var = "PWD=";
	if (getcwd(pwd_value, 256) == NULL)
	{
		perror("cd");
		return (NULL);
	}
	pwd_entry = malloc(_strlen(pwd_var) + _strlen(pwd_value) + 1);
	_strcpy(pwd_entry, pwd_var);
	_strcat(pwd_entry, pwd_value);
	if (_putenv(pwd_entry) != 0)
	{
		perror("cd");
		free(pwd_entry);
		return (NULL);
	}

	free(pwd_entry);

	return (NULL);	/* Return NULL as no command output is expected */
}




























char* get_cmd(char* cmd, ..., char (*_getenv)(const char *name))
{
	int stat;
	va_list(stts);
	char* path;
	char* cd;
	char* exit;
	char* env;

	environ = my_environ;
	va_start(stts, cmd);

	if (_strcmp(cmd, "path") == 0)
	{
		path = _getenv("PATH");
		if (path == NULL)
		{
			perror("Failed to retrieve PATH");
			exit(EXIT_FAILURE);
		}
	}
	else if (_strcmp(cmd, "cd") == 0)
	{
		cd = _getenv("CD")
	}

	
}
