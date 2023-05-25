#include "main.h"

/**
 * _strncpy - copies a string
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 * @n: maximum number of bytes to copy from src
 *
 * Return: pointer to the resulting string dest
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i;

    /* Copy up to n characters from src to the dest */
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    /* If src is shorter than n, pad dest with null terminators */
    for ( ; i < n; i++)
    {
        dest[i] = '\0';
    }

    return (dest);
}

/**
 * _Strlen - counts const chars in a string.
 *
 * @s: unsigned char used
 *
 * Return: Length of string
 */

int _Strlen(const char *s)
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
 * _Strcpy - Copies the string pointed to by src, including the terminating
 * null byte (\0), to the buffer pointed to by dest.
 *
 * @dest: Buffer to copy string to.
 * @src: String to copy.
 *
 * Return: Pointer to dest.
 */
char *_Strcpy(char *dest, const char *src)
{
    int i;

    for (i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    dest[i] = '\0';

    return (dest);
}
