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
