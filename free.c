#include "main.h"

/**
 * freeArguments - Frees the arguments
 * @args: Tokenized arguments
 * Return: void
 */
void freeArguments(char **args)
{
	int index;
	int len = 0;

	while (args[len] != NULL)
		len++;

	for (index = 0; index < len; index++)
	{
		free(args[index]);
	}
}

/**
 * freePath - Frees the path
 * @path: Pointer to the linked path
 * Return: void
 */
void freePath(LinkedPath *path)
{
	LinkedPath *temp;

	while (path != NULL)
	{
		temp = path->next;
		free(path->dir);
		free(path);
		path = temp;
	}
}

/**
 * freeEnvironment - Frees the environment variables
 * Return: void
 */
void freeEnvironment(void)
{
	int index;

	for (index = 0; environ[index] != NULL; index++)
	{
		free(environ[index]);
	}
	free(environ);
}
