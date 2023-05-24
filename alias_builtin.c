#include "main.h"

/**
 * checkAlias - Checks if an Alias exists
 * @neww: List of arguments
 * Return: Name of Alias if it exists, NULL otherwise
 */
char *checkAlias(char *neww)
{
	Alias *temp = getAliasList();

	while (temp != NULL)
	{
		if (strcmp(neww, temp->newCmd) == 0)
		{
			return (temp->newCmd);
		}
		temp = temp->next;
	}
	return (NULL);
}

/**
 * executeCommandAlias - executeCommands an Alias command
 * @main: Main command
 * @args: List of arguments
 * Return: Always 0 (Success)
 */
int executeCommandAlias(char *main, char **args)
{
	if (execve(main, args, environ) == -1)
	{
		fprintf(stderr, "%s: No such file or directory\n", args[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * createKeyValuePair - Creates an Alias key-value pair
 * @name: Argument to be initialized into the name_command
 * @Alias_list: Pointer to the Alias list
 * @equals: Pointer to the '=' in the args
 * Return: 0 on success, -1 on failure
 */
int createKeyValuePair(Alias **Alias_list, char *name, char *equals)
{
	Alias *list_copy = *Alias_list;
	int i, b = 0, j, value_length;
	char *mainCmd, *new_command = malloc((strlen(name) + 1) * sizeof(char));

	while (name[b] != '=')
	{
		new_command[b] = name[b];
		b++;
	}

	*equals = '\0';
	equals = equals + 1;

	printf("Now allocating memory for value_command equals = %s\n", equals);
	value_length = strlen(equals) - strspn(equals, "'\"");
	mainCmd = malloc(sizeof(char) * (value_length + 1));

	printf("Now Entering Initialization loop\n");
	for (i = 0, j = 0; equals[i] != '\0'; i++)
	{
		if (equals[i] != '\'' && equals[i] != '"')
		{
			mainCmd[j] = equals[i];
			j++;
		}
	}
	mainCmd[j] = '\0';

	printf(" Before adding : name = %s, value = %s\n", new_command, mainCmd);
	*Alias_list = addAlias(&list_copy, new_command, mainCmd);

	return (0);
}

/**
 * addAlias - Adds an Alias to the list
 * @head: Pointer to the head of the Alias list
 * @new: Name of the new command
 * @main: Name of the main command
 * Return: Pointer to the head of the Alias list
 */
Alias *addAlias(Alias **head, char *new, char *main)
{
	Alias *new_node = malloc(sizeof(Alias));
	Alias *temp;

	new_node->mainCmd = strdup(main);
	new_node->newCmd = strdup(new);
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			if (strcmp(new, temp->newCmd) == 0)
			{
				free(temp->mainCmd);
				temp->mainCmd = strdup(main);
				free(new_node->mainCmd);
				free(new_node->newCmd);
				return (*head);
			}
			temp = temp->next;
		}
		temp->next = new_node;
	}
	printf("Added Alias to the list successfully \n");

	temp = *head;
	while (temp != NULL)
	{
		printf("Alias: %s='%s'\n", temp->newCmd, temp->mainCmd);
		temp = temp->next;
	}
	return (*head);
}

/**
 * printAliasList - Prints the Alias list
 * @head: Pointer to the head of the Alias list
 * Return: Always 0 (Success)
 */
int printAliasList(Alias *head)
{
	Alias *temp = head;

	while (temp != NULL)
	{
		printf("Alias: %s='%s'\n", temp->newCmd, temp->mainCmd);
		temp = temp->next;
	}
	printf(" Printed list successfully \n");

	return (0);
}
