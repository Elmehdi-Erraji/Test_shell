#include "main.h"

/**
 * isBuiltInCommand - Checks if the command is a built-in command and executeCommands it
 * @args: Command and arguments
 * @line_num: Execution count
 * Return: 1 if it's a built-in command, 0 otherwise
 */
int isBuiltInCommand(char **args, int line_num)
{
	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
	{
		exitShell(args);
		exit(EXIT_SUCCESS);
	}
	if (strcmp(args[0], "env") == 0)
	{
		showEnvironment();
		return (1);
	}
	if (strcmp(args[0], "cd") == 0)
	{
		changeDirectory(args, line_num);
		return (1);
	}
	if (strcmp(args[0], "setenv") == 0)
	{
		setEnvironmentVariable(args[1], args[2], 1);
		return (1);
	}
	if (strcmp(args[0], "unsetenv") == 0)
	{
		unsetEnvironmentVariable(args);
		return (1);
	}
	return (0);
}

/**
 * built_ins2 - Checks if the command is a built-in command and executeCommands it
 * @args: Command and arguments
 * @line_num: Execution count (unused)
 * Return: 1 if it's a built-in command, 0 otherwise
 */
int isBuiltInCommand2(char **args, int line_num __attribute__ ((unused)))
{
	if (strcmp(args[0], "Alias") == 0)
	{
		setAlias(args);
		return (1);
	}

	if (strcmp(args[0], "echo") == 0)
	{
		echoCommand(args);
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}

	return (0);
}
