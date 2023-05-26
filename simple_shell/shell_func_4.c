#include "main.h"

/**
 * _strstr - Locate a substring
 * @haystack: Pointer to the string to search within
 * @needle: Pointer to the substring to find
 *
 * Description:
 * The _strstr() function finds the first occurrence of the substring @needle
 * in the string @haystack. The terminating null bytes ('\0') are not compared.
 *
 * Return: A pointer to the beginning of the found substring in @haystack,
 *         or NULL if the substring is not found.
 */
char *_strstr(const char *haystack, const char *needle)
{
	const char *h, *n;

	if (*needle == '\0')
	{
		return (char *)haystack;
	}

	while (*haystack != '\0')
	{
		h = haystack;
		n = needle;

		while (*n != '\0' && *h == *n)
		{
			h++;
			n++;
		}

		if (*n == '\0')
		{
			return (char *)haystack;
		}

		haystack++;
	}

	return (NULL);
}

/**
 * _strcspn - Get the length of a prefix substring
 * @str: Pointer to the string to search within
 * @reject: Pointer to the string containing characters to reject
 *
 * Description:
 * The _strcspn() function calculates the length of the initial segment of @str,
 * which consists of characters not found in the string @reject. The search
 * does not include the terminating null byte ('\0') of @str.
 *
 * Return: The length of the prefix substring in @str, consisting of characters
 *         not found in @reject.
 */
size_t _strcspn(const char *str, const char *reject)
{
	const char *s, *r;
	size_t count = 0;

	while (*str != '\0')
	{
		s = str;
		r = reject;

		while (*r != '\0')
		{
			if (*s == *r)
			{
				return count;
			}

			r++;
		}

		str++;
		count++;
	}

	return (count);
}
