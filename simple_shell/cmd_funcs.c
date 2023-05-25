#include "main.h"

/**
 * exit_cmd - Terminate the program with the specified status code.
 *
 * @cmd: Command to execute code.
 *
 * Description:
 * This function terminates the program with the specified status code. If no
 * status code is provided, the default behavior is determined by the operating
 * system or environment.
 */

void exit_cmd(const char* cmd, ...)
{
    int status; /* extract the status from the arguments */

	va_list args;
	va_start(args, cmd);

	if (_strcmp(cmd, "exit") == 0)
	{
		status = va_arg(args, int);
		va_end(args);

		exit(status);
	}
	va_end(args);
}

/**
 * env_cmd - Display environment variables.
 *
 * @cmd: The command string.
 *
 * Return: A dynamically allocated string containing the captured output,
 *         or NULL on failure.
 */
char *env_cmd(const char *cmd)
{
    extern char **environ; /* Access the global environ variable */

    /* Iterate over each environment variable and capture them in a string */
    char **envi = environ;
    size_t total_len = 0;
    size_t cmd_len = _strlen(cmd);
    char *output;
    char *tmp;
	sixe_t len;

    if (_strcmp(cmd, "env") == 0)
    {
        /* Calculate the total length of the captured output */
        while (*envi != NULL)
        {
            len = _strlen(*envi);
            total_len += len + 1; /* +1 for newline character */
            envi++;
        }

        /* Allocate memory for the output string */
        output = malloc(total_len + cmd_len + 1); /* +1 for null terminator */
        if (output == NULL)
        {
            perror("env");
            return (NULL);
        }

        tmp = output;

        /* Copy the command to the beginning of the output string */
        _strcpy(tmp, cmd);
        tmp += cmd_len;

        envi = environ;

        /* Copy the environment variables to the output string */
        while (*envi != NULL)
        {
            len = _strlen(*envi);
            _strcpy(tmp, *envi);
            tmp += len;

            /* Add newline character after each environment variable */
            *tmp = '\n';
            tmp++;

            envi++;
        }

        *tmp = '\0'; /* Add null terminator at the end */
    }

    return (output);
}


/**
 * setenv_cmd - Set or update an environment variable.
 *
 * @cmd: The command string containing the variable name and value.
 *
 * Return: NULL on success, or an error message on failure.
 */

char *setenv_cmd(const char *cmd, ...)
{
	va_list args;
	char *name, *value;
	size_t var_len;
	size_t value_len;
	size_t str_len;
	char *env_str;
	char **env;
	size_t env_count;
	size_t new_env_count, i;
	char **new_env;

	if (_strcmp(cmd, "setenv") == 0)
	{
		va_start(args, cmd);

		/* Parse the command string to extract the variable name and value */
		name = va_arg(args, char *);
		value = va_arg(args, char *);

		va_end(args);

		/* Check if both name and value are provided */
		if (name == NULL || value == NULL)
		{
			return ("Usage: setenv VAR VALUE");
		}

		/* Concatenate name, "=", and value into a single string */
		var_len = _strlen(name);
		value_len = _strlen(value);
		str_len = var_len + 1 + value_len + 1; /* +1 for '=', +1 for null terminator */
		env_str = malloc(str_len);
		if (env_str == NULL)
		{
			return ("Failed to allocate memory");
		}

		_strcpy(env_str, name);
		env_str[var_len] = '=';
		_strcpy(env_str + var_len + 1, value);

		/* Search for the existing variable in the environ array */
		env = environ;
		while (*env != NULL)
		{
			if (_strncmp(*env, name, var_len) == 0 && (*env)[var_len] == '=')
			{
				/* Found the variable, replace it with the new value */
				free(*env);
				*env = env_str;
				return (NULL);	/* Return NULL on success */
			}
			env++;
		}

		/* Variable not found, calculate the size of the new environ array */
		env_count = env - environ;	/* Get the number of existing variables */
		new_env_count = env_count + 2;	/* +2 for the new variable and NULL terminator */

		/* Allocate memory for the new environ array */
		new_env = malloc(8 * new_env_count);
		if (new_env == NULL)
		{
			free(env_str);
			return ("Failed to allocate memory");
		}

		/* Copy the existing variables to the new environ array */
		for (i = 0; i < env_count; i++)
		{
			new_env[i] = environ[i];
		}

		/* Add the new variable and NULL terminator to the new environ array */
		new_env[env_count] = env_str;
		new_env[new_env_count - 1] = NULL;

		/* Replace the environ array with the new one */
		free(environ);
		environ = new_env;

		return (0); /* Return NULL on success */
	}

	return (-1);
}

/**
 * unsetenv_cmd - Unset an environment variable.
 *
 * @cmd: The command string containing the variable name.
 *
 * Return: NULL on success, or an error message on failure.
 */
char *unsetenv_cmd(const char *cmd, ...)
{
	va_list args;
	char *name;
	char **src;
	char **dst;
	char **env;

	va_start(args, cmd);

	if (_strcmp(cmd, "unsetenv") == 0)
	{
		/* Parse the command string to extract the variable name */
		name = va_arg(args, char *);

		va_end(args);

		/* Check if name is provided */
		if (name == NULL)
		{
			return ("Usage: unsetenv VAR");
		}

		/* Search for the variable in the environ array */
		env = environ;
		while (*env != NULL)
		{
			if (strcmp(*env, name) == 0)
			{
				/* Variable found, remove it from the environ array */
				free(*env);

				/* Shift the remaining variables to fill the gap */
				src = env + 1;
				dst = env;
				while (*src != NULL)
				{
					*dst = *src;
					src++;
					dst++;
				}
				*dst = NULL;

				return (NULL);	/* Return NULL on success */
			}
			env++;
		}
	}

	/* Variable not found */
	return ("Variable not found");
}



char *cd_cmd(const char* cmd, ...)
{
	va_list args;
    char *dir;
	char target_dir[256];
    char *home_dir;
    char *old_dir;
	char current_dir[256];
	char pwd_value[256];
	char *pwd_var;
	char *pwd_entry;

	if (_strcmp(cmd, "cd") == 0)
	{
		/* Parse variable arguments */
		va_start(args, cmd);
		dir = va_arg(args, char *);
		va_end(args);

		/* Determine the target directory */
		if (dir == NULL || _strcmp(dir, "") == 0)
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
		else if (_strcmp(dir, "-") == 0)
		{
			/* If the argument is "-", change to the previous directory (stored in $OLDPWD) */
			old_dir = _getenv("OLDPWD");
			if (old_dir == NULL)
			{
				perror("cd");
				return (NULL);
			}
			_strncpy(target_dir, old_dir, 256);
		}
		else
		{
			/* Use the provided directory argument */
			_strncpy(target_dir, dir, 256);
		}

		/* Save the current working directory to $OLDPWD */
		if (getcwd(current_dir, 256) == NULL)
		{
			perror("cd");
			return (NULL);
		}
		if (setenv_cmd("OLDPWD", current_dir) != NULL)
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
		_strcpy(pwd_entry, pwd_var);
		_strcat(pwd_entry, pwd_value);
		if (setenv_cmd("PWD", pwd_value) != NULL)
		{
			perror("cd");
			free(pwd_entry);
			return (NULL);
		}
	}

	free(pwd_entry);

	return (NULL);	/* Return NULL as no command output is expected */
}
