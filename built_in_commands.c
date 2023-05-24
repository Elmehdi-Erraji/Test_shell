#include "main.h"

/**
 * showEnvironment - Prints the environment variables
 *
 * Return: Always 0 (Success)
 */
int showEnvironment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}

	return (0);
}


/**
 * changeDirectory - Changes the current directory
 * @args: Arguments passed
 * @line_num: Command count
 * Return: Always 0 (Success)
 */
int changeDirectory(char **args, int line_num)
{
	char *new_dir, *old_dir;
	char cwd[1024];
	char *cd_err = getErrorDirectory(args);

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
		new_dir = getEnvironmentVariable("HOME");
	else if (strcmp(args[1], "-") == 0)
		new_dir = getEnvironmentVariable("OLDPWD");
	else
		new_dir = args[1];

	old_dir = getEnvironmentVariable("PWD");

	if (setEnvironmentVariable("OLDPWD", old_dir, 1) != 0)
	{
		perror("Could not set OLDPWD environment variable");
		return (1);
	}

	if (chdir(new_dir) != 0)
	{
		printErrorMessage(args[0], cd_err, line_num);
		return (1);
	}

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Could not get current directory");
		return (1);
	}
	if (setEnvironmentVariable("PWD", cwd, 1) != 0)
	{
		perror("Could not set PWD environment variable");
		return (1);
	}

	return (0);
}


/**
 * setEnvironmentVariable - Sets the value of an environment variable
 * @name: Name of the environment variable
 * @value: Environment value
 * @overwrite: Replace variable
 * Return: Always 0 (Success)
 */
int setEnvironmentVariable(const char *name, const char *value, int overwrite)
{
	int i, j;
	int len;
	char *env;

	if (name == NULL || value == NULL)
	{
		perror("Invalid arguments");
		return (1);
	}
	len = strlen(name) + strlen(value) + 2;
	env = malloc(len);
	if (env == NULL)
	{
		perror("Memory allocation failed");
		return (1);
	}

	for (i = 0; name[i] != '\0'; i++)
	{
		env[i] = name[i];
	}
	env[i] = '=';

	for (j = 0; value[j] != '\0'; j++)
	{
		env[i + j + 1] = value[j];
	}
	env[i + j + 1] = '\0';

	if (overwrite == 0 && getEnvironmentVariable(name) != NULL)
	{
		return (0);
	}
	if (putenv(env) != 0)
	{
		perror("Setting environment variable failed");
		return (1);
	}
	return (0);
}

/**
 * unsetEnvironmentVariable - Unsets an environment variable
 * @args: Command and arguments
 * Return: Always 0 (Success)
 */
int unsetEnvironmentVariable(char **args)
{
	int i, j;
	char *name = args[1];
	int len = strlen(name);

	if (args[1] == NULL || args[2] != NULL)
	{
		perror("Invalid argument");
		return (1);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			for (j = i; environ[j] != NULL; j++)
			{
				environ[j] = environ[j + 1];
			}
			break;
		}
	}

	return (0);
}


/**
 * exitShell - Exits the shell
 * @args: Command and arguments
 * Return: Always 0 (Success)
 */
int exitShell(char **args)
{
	unsigned int getExitStatus = 0;
	unsigned int max = 1 << (sizeof(int) * 8 - 1);
	int i = 0, len = 10;

	if (args[1] != NULL)
	{
		if (args[1][0] == '+')
		{
			i = 1;
			len++;
		}

		if (args[1][i] != '\0')
		{
			while (args[1][i] != '\0')
			{
				if (i <= len && args[1][i] >= '0' && args[1][i] <= '9')
				{
					getExitStatus = (getExitStatus * 10) + (args[1][i] - '0');
				}
				else
				{
					printf("Invalid exit status.\n");
					return (-1);
				}
				i++;
			}

			if (getExitStatus > max - 1)
			{
				printf("Invalid exit status.\n");
				return (-1);
			}
		}
	}
	exit(getExitStatus);
}
