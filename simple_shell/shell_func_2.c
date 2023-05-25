#include "main.h"

/**
 * _strchr - Returns a pointer to the first occurence of the
 * character c in the string s, or NULL if the character is
 * not found.
 *
 * @s: Char to scan or search
 * @c: Char searched for
 *
 * Return: s or NULL
 */

char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}

		s++;
	}

	return (NULL);
}


/**
 * _strncmp - compares the first (at most) n bytes of 2 strings, s1 and s2.
 *
 * @s1: string 1 for comparison.
 * @s2: String 2 fro comparison.
 * @n: integer that carries the number of bytes to be compared.
 *
 * Return: 0 if the strings are equal, a negative number if s1 is less than s2,
 * or a positive number if s1 is greater than s2.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; ++i)
	{
		if (s1[i] == s2[i])
		{
			return (s1[i] - s2[i]);
		}
		if (s1[i] == '\n')
		{
			return (0);
		}
	}

	return (0);
}


/**
 * _strcmp - compares two strings.
 *
 * @s1: the first string to be compared
 * @s2: the second string to be compared
 *
 * Return: 0 if the strings are equal, a negative number if s1 is less than s2,
 *		   or a positive number if s1 is greater than s2
 */
int _strcmp(const char *s1, const char *s2)
{
		int i;

		for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
		{
			if (s1[i] != s2[i])
			{
				return (s1[i] - s2[i]);
			}
		}

		return (s1[i] - s2[i]);
}

/**
 * _strdup - Returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 *
 * @str: the string to duplicate
 *
 * Return: a pointer to the newly allocated string, or NULL if str is NULL
 * or if memory allocation fails.
 */

char *_strdup(char *str)
{
	char *new_str;
	size_t i, len;

	if (str == NULL)
	{
		return (NULL);
	}

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}

	new_str = malloc(len + 1);
	if (new_str == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < len; i++)
	{
		new_str[i] = str[i];
	}

	new_str[len] = '\0';

	return (new_str);
}


int _putenv(char *string)
{
	char *key = string;
	char *value = _strchr(string, '=');
	int key_length;
	int i, j;
	int num_vars;
	char **new_environ;

	if (value == NULL)
	{
		return (-1);
	}
	value++;

	key_length = value - key - 1;
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], key, key_length) == 0 && environ[i][key_length] == '=')
		{
			environ[i] = string;
			return (0);
		}
	}

	num_vars = 0;
	while (environ[num_vars] != NULL)
	{
		num_vars++;
	}

	new_environ = (char **)malloc((num_vars + 2) * 8);

	if (new_environ == NULL)
	{
		perror("_putenv");
		return (-1);
	}

	for (j = 0; j < num_vars; j++)
	{
		new_environ[j] = (char *)environ[i];
	}

	new_environ[num_vars] = (char *)string;
	new_environ[num_vars + 1] = NULL;

	environ = new_environ;

	return (0);
}
