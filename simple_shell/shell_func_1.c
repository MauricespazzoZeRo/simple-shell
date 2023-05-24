#include "main.h"

/**
 * _getline - reads input from a stream and stores it in a buffer
 *
 * Return: number of bytes read on success, -1 on failure or end-of-file
 */
char* _getline(void)
{
	static char buffer[BUFFER_SIZE]; /* Buffer for reading input from stdin */
	static int pos = 0; /* Tracks the current position of buffer */
	static int size = 0; /* Stores number of chars in the buffer */

	char* line = NULL; /* pointer to line being constructed */
	char* new_line; /* Temp pointer to line being constructed while resizing */
	int capacity = 0; /* Current capacity of line, max chars in buffer w/o resizing */
	int length = 0; /* Tracks current length of line, num of chars in buffer so far */
	int i;
	char c;

	for ( ;	 ; )
	{
		/* If we have consumed all characters in the buffer, read more input. */
		if (pos == size)
		{
			/* Update size: chars in buffer */
			size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			pos = 0;

			/* If we have reached the end of the input, return the line. */
			if (size == 0)
			{
				if (line)
				{
					line[length] = '\0';
					return (line);
				}
				return (NULL);
			}
		}

		/* Resize the line buffer if necessary. */
		if (length + 1 >= capacity)
		{
			capacity = capacity == 0 ? BUFFER_SIZE : capacity * 2;
			new_line = malloc(capacity);
			if (!new_line)
			{
				if (line)
				{
					free(line);
				}
				return (NULL);
			}
			if (line)
			{
				for (i = 0; i < length; i++)
				{
					new_line[i] = line[i];
				}
				free(line);
			}
			line = new_line;
		}

		/* Add the next character to the line buffer. */
		c = buffer[pos++];
		if (c == '\n')
		{
			line[length] = '\0';
			return line;
		}
		else
		{
			line[length++] = c;
		}
	}
}


/**
 * _strlen - counts chard in a string.
 *
 * @s: unsigned char used
 *
 * Return: Nothing
 */

int _strlen(char *s)
{
	int length = 0;

	while (*s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}

/**
 * _getenv - function to search through environ and get variables when needed.
 *
 * @name: Variable name of command(s) in environ.
 *
 * Return: char; variable value for needed variable in environ OR NULL if no
 *		   matching variable name is found.
 */

char *_getenv(const char *name)
{
	int i;
	size_t name_len;
	char* equal_sign_pos;

/* Check if the name is NULL */
	if (name == NULL)
	{
		return (NULL);
	}

	/* Iterate through the environment variables */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Find the position of the equal sign '=' */
		equal_sign_pos = _strchr(environ[i], '=');
		if (equal_sign_pos != NULL)
		{
			/* Calculate the length of the variable name */
			name_len = equal_sign_pos - environ[i];

			/* Compare the variable name with the given name */
			if (_strncmp(environ[i], name, name_len) == 0 && name[name_len] == '\0')
			{
				/* Return the value part of the environment variable */
				return (equal_sign_pos + 1);
			}
		}
	}

	/* Return NULL if the variable is not found */
	return (NULL);
}

/**
 * _strcat -  Concatenates two strings.
 *
 * Appends the src string to the dest string, overwriting the
 * terminating null byte (\0) at the end of dest, and then adds a
 * terminating null byte.
 *
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the resulting string dest.
 */
char *_strcat(char *dest, char *src)
{
	char *result = dest;

	/* Move the pointer to the end of dest string */
	while (*dest != '\0')
	{
		dest++;
	}

	/* Copy the src string to the end of dest string */
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	/* Add the terminating null byte */
	*dest = '\0';

	return (result);
}

/**
 * _strcpy - Copies the string pointed to by src, including the terminating
 * null byte (\0), to the buffer pointed to by dest.
 *
 * @dest: Buffer to copy string to.
 * @src: String to copy.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
    int i;

    for (i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    dest[i] = '\0';

    return dest;
}
