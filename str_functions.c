#include "main.h"

/**
 * stringLength - Calculates the length of a string
 * @s: Input string
 * Return: Length of the string
 */
int stringLength(const char *s)
{
	int length;

	if (s == NULL)
		return (-1);

	length = 0;
	while (s[length] != '\0')
		length++;
	return length;
}

/**
 * stringCompare - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: Result of the comparison
 */
int stringCompare(const char *s1, const char *s2)
{
	const char *p1 = s1;
	const char *p2 = s2;
	int i = 0;

	if (p1 == NULL && p2 == NULL)
		return (0);
	else if (p1 == NULL)
		return (-1);
	else if (p2 == NULL)
		return (1);

	while (*(p1 + i) != '\0' && *(p2 + i) != '\0' && p1[i] == p2[i])
	{
		i++;
	}
	return (p1[i] - p2[i]);
}

/**
 * stringCharacter - Locates a character in a string
 * @s: Input string
 * @c: Character to be located
 * Return: Pointer to the first occurrence of the character, or NULL if not found
 */
char *stringCharacter(const char *s, const char c)
{
	const char *p = s;
	const char *pp = &c;
	int i;

	for (i = 0; *(p + i) != '\0'; i++)
	{
		if (*(p + i) == *pp)
		{
			return ((char *)(s + i));
		}
	}

	return NULL;
}

/**
 * stringDuplicate - Duplicates a string
 * @str: Input string
 * Return: Pointer to the duplicated string, or NULL if allocation fails
 */
char *stringDuplicate(const char *str)
{
	int i, len = 0;
	char *result;

	if (str == NULL)
		return NULL;

	for (; str[len] != '\0'; len++)
		;

	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return NULL;

	for (i = 0; i <= len; i++)
		result[i] = str[i];

	return result;
}

/**
 * stringCompareN - Compares two strings up to a maximum number of characters
 * @s1: First string
 * @s2: Second string
 * @n: Maximum number of characters to compare
 * Return: Result of the comparison
 */
int stringCompareN(const char *s1, const char *s2, size_t n)
{
	unsigned char p1, p2;
	size_t i;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	for (i = 0; i < n; i++)
	{
		p1 = (unsigned char)s1[i];
		p2 = (unsigned char)s2[i];

		if (p1 != p2)
			return (p1 - p2);
		if (p1 == '\0')
			break;
	}

	return 0;
}
