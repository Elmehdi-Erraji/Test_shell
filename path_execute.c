#include "main.h"

/**
 * executeCommandWithPath - executeCommands a command from the path
 * @args: Array of tokenized commands
 * Return: The process id
 */
int executeCommandWithPath(char **args)
{
	LinkedPath *temp = linkPath();
	char fullpath[1024];

	while (temp != NULL)
	{
		sprintf(fullpath, "%s/%s", temp->dir, args[0]);
		if (access(fullpath, F_OK) == 0)
		{
			execve(fullpath, args, NULL);
		}
		temp = temp->next;
	}
	return (-1);
}

/**
 * checkPath - Checks for a command in the path
 * @args: Command to check
 * Return: 1 if command found, -1 otherwise
 */
int checkPath(char **args)
{
	LinkedPath *temp = linkPath();
	char fullpath[1024];

	while (temp != NULL)
	{
		sprintf(fullpath, "%s/%s", temp->dir, args[0]);
		if (access(fullpath, F_OK) == 0)
		{
			return (1);
		}
		temp = temp->next;
	}
	return (-1);
}

/**
 * linkPath - Creates a linked list for the path
 * Return: A pointer to the first node
 */
LinkedPath *linkPath(void)
{
	char *dir;
	char *path;
	char *pathDup;
	LinkedPath *head;
	LinkedPath *currentNode = (LinkedPath *)malloc(sizeof(LinkedPath));

	head = currentNode;

	path = getEnvironmentVariable("PATH");
	pathDup = strdup(path);
	dir = stringTokenize(pathDup, ":");
	currentNode->dir = strdup(dir);

	while (dir != NULL)
	{
		dir = stringTokenize(NULL, ":");
		if (dir != NULL)
		{
			currentNode->next = (LinkedPath *)malloc(sizeof(LinkedPath));
			currentNode = currentNode->next;
			currentNode->dir = strdup(dir);
		}
	}
	currentNode->next = NULL;

	return (head);
}
