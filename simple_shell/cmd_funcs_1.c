#include "main.h"

void print_aliases()
{
	int i;
	
	for (i = 0; i < MAX_ALIASES; i++)
	{
		if (aliases[i].name != NULL && aliases[i].value != NULL)
		{
			write(STDOUT_FILENO, aliases[i].name, strlen(aliases[i].name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, "'", 1);
			write(STDOUT_FILENO, aliases[i].value, strlen(aliases[i].value));
			write(STDOUT_FILENO, "'\n", 2);
		}
	}
}

void print_alias(const char *alias_name)
{
	int i;
	
	for (i = 0; i < MAX_ALIASES; i++)
	{
		if (aliases[i].name != NULL && _strcmp(aliases[i].name, alias_name) == 0)
		{
			write(STDOUT_FILENO, aliases[i].name, _strlen(aliases[i].name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, "'", 1);
			write(STDOUT_FILENO, aliases[i].value, _strlen(aliases[i].value));
			write(STDOUT_FILENO, "'\n", 2);
			return;
		}
	}
}

void define_alias(const char *alias_name, const char *alias_value)
{
	int i, j;
	
	for (i = 0; i < MAX_ALIASES; i++)
	{
		if (aliases[i].name != NULL && _strcmp(aliases[i].name, alias_name) == 0)
		{
			free(aliases[i].value);
			aliases[i].value = strdup(alias_value);
			return;
		}
	}

	for (j = 0; j < MAX_ALIASES; j++)
	{
		if (aliases[i].name == NULL)
		{
			aliases[i].name = strdup(alias_name);
			aliases[i].value = strdup(alias_value);
			return;
		}
	}
	
	write(STDOUT_FILENO, "Maximum number of aliases reached.\n", 35);
}

char *alias_cmd(const char *cmd, ...)
{
	va_list args;
	char *alias_name;
	char *next_arg;
	
	va_start(args, cmd);

	if (_strcmp(cmd, "alias") == 0)
	{
		alias_name = va_arg(args, char *);
		if (alias_name == NULL)
		{
			print_aliases();
			return (NULL);
		}

		next_arg = va_arg(args, char *);
		if (next_arg == NULL)
		{
			print_alias(alias_name);
			return (NULL);
		}

		while (next_arg != NULL)
		{
			define_alias(alias_name, next_arg);
			alias_name = va_arg(args, char *);
			next_arg = va_arg(args, char *);
		}
	}
	
	return (NULL);
}
