#include "main.h"

/**
 * stringConcatenate - Concatenates two strings
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the concatenated string
 */
char *stringConcatenate(char *dest, const char *src)
{
	char *p = dest;

	while (*p)
	{
		p++;
	}
	if (src)
	{
		while (*src)
		{
			*p++ = *src++;
		}
	}
	*p = '\0';

	return dest;
}


/**
 * stringCopy - Copies a string
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string
 */
char *stringCopy(char *dest, const char *src)
{
	char *p;

	while (*src == ' ')
	{
		src++;
	}

	p = dest;
	while (*src)
	{
		*p++ = *src++;
	}

	while (p > dest && *(p - 1) == ' ')
	{
		p--;
	}

	*p = '\0';

	return dest;
}
