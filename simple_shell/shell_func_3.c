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



/**
 * _memmove - Copy a block of memory
 * @dest: Pointer to the destination memory block
 * @src: Pointer to the source memory block
 * @n: Number of bytes to copy
 *
 * Description:
 * The _memmove() function copies @n bytes from the memory area pointed to by
 * @src to the memory area pointed to by @dest. The memory areas may overlap,
 * and the copy is done in a non-destructive manner.
 *
 * Return: A pointer to the destination memory block @dest.
 */
void *_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *)src;
	size_t i;

	if (d == s)
	{
		return (d);
	}

	if (s < d && d < s + n)
	{
		while (n--)
		{
			d[n] = s[n];
		}
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			d[i] = s[i];
		}
	}

	return (d);
}


/**
 * memcpy - Copies n bytes from memory area src to memory area dest
 *
 * @dest: Destination to receive copied chars
 * @src: Source from which char will be copied
 * @n: Number of bytes that will be copied from src
 *
 * Return: A pointer to dest
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	char *tst_dest = dest;
	char *tst_src = src;
	unsigned int arrmem = 0;

	while ((n > 0) && (arrmem < n))
	{
		arrmem++;
		tst_dest[arrmem] = tst_src[arrmem];
	}

	return (dest);
}
