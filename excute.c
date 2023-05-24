#include "main.h"

/**
 * executeCommand - executeCommands a command
 * @command: Command passed
 * @line_num: Line number to track commands
 * Return: ID of fork
 */
int executeCommand(char *command, int line_num)
{
	char *args[MAX_ARGS];
	char command_path[MAX_PATH_LENGTH];
	pid_t pid;
	int i;

	i = tokenizeCommand(command, args);
	args[i] = NULL;

	if (isBuiltInCommand(args, line_num) || isBuiltInCommand2(args, line_num))
		return (0);
	if (access(args[0], X_OK) == -1)
	{
		strcpy(command_path, "/bin/");
		strcat(command_path, args[0]);
		if (access(command_path, X_OK) == -1)
		{
			printErrorMessage(args[0], "not found", line_num);
			return (0);
		}
	}

	pid = fork();

	if (pid == -1)
		exit(EXIT_FAILURE);

	if (pid != 0)
		runParentProcess();

	if (pid == 0 && args[0][0] != '\0')
	{
		runChildProcess(args);
	}

	return (0);
}


/**
 * runChildProcess - executeCommands the child process
 * @args: Command passed
 * Return: ID of fork
 */
int runChildProcess(char **args)
{
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (checkPath(args) == 1)
	{
		executeCommandWithPath(args);
	}
	else
	{
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * runParentProcess - executeCommands the parent process
 *
 * Return: ID of fork
 */
int runParentProcess(void)
{
	getExitStatus();
	return (0);
}

/**
 * getExitStatus - Retrieves the exit status of the child process
 *
 * Return: Exit status
 */
int getExitStatus(void)
{
	int status;
	static int exitStatusValue;

	wait(&status);

	if (WIFEXITED(status))
	{
		exitStatusValue = WEXITSTATUS(status);
	}
	return exitStatusValue;
}