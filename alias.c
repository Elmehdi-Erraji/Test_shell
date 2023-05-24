#include "main.h"

/**
 * setAlias - Handles the "Alias" command
 * @args: List of commands
 * Return: Always 0 (Success)
 */
int setAlias(char **args)
{
	int i = 1;
	Alias *list_copy = getAliasList();
	char *equals;

	if (args[i] == NULL)
	{
		if (list_copy == NULL)
			printf("NULL\n");
		else
		{
			printf("Wants to enter printAliasList\n");
			printAliasList(list_copy);
		}
		return (0);
	}
	for (i = 1; args[i] != NULL; i++)
	{
		equals = strchr(args[i], '=');
		list_copy = getAliasList();
		if (equals == NULL)
		{
			while (list_copy != NULL)
			{
				if (strcmp(args[i], list_copy->mainCmd) == 0)
				{
					printAliasList(list_copy);
					break;
				}
				list_copy = list_copy->next;
			}
		}
		else
		{
			printf("Calling createKeyValuePair function. args = %s\n", args[i]);
			createKeyValuePair(&list_copy, args[i], equals);
		}
	}
	return (0);
}

/**
 * getAliasList - Returns the Alias list
 * Return: The Alias list
 */
Alias *getAliasList(void)
{
	Alias *Alias_list = NULL;

	return (Alias_list);
}
