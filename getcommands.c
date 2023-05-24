#include "main.h"

/**
 * getDiretory - Prints the working directory
 * Return: The working directory
 */
char *getDiretory()
{
	char *cwd = malloc(sizeof(char) * 1024);

	if (cwd == NULL)
	{
		perror("malloc error");
		return (NULL);
	}

	if (getcwd(cwd, 1024) != NULL)
	{
		return (cwd);
	}
	else
	{
		perror("getcwd error");
		free(cwd);
		return (NULL);
	}
}

/**
 * getEnvironmentVariable - Checks for a variable in the environment
 * @name: Pointer to an array of characters
 * Return: Pointer if success, NULL if failed
 */
char *getEnvironmentVariable(const char *name)
{
	int i = 0;
	char *envi_ron;
	char *equals;

	while (environ[i] != NULL)
	{
		envi_ron = environ[i];
		equals = strchr(envi_ron, '=');

		*equals = '\0';
		if (strcmp(envi_ron, name) == 0)
		{
			*equals = '=';
			return (environ[i] + strlen(name) + 1);
		}
		*equals = '=';
		i++;
	}
	return (NULL);
}

/**
 * getLine - Reads a line from input stream
 * @buffer: Pointer to hold command and arguments
 * @bufsize: Size of buffer
 * @fd: File descriptor of input stream
 * Return: Length of the string buffer
 */
ssize_t getLine(char **buffer, size_t *bufsize, int fd)
{
	static size_t line_buffer_size = 1024;
	ssize_t read_bytes;
	size_t len = 0;
	*bufsize = line_buffer_size;
	*buffer = malloc(*bufsize * sizeof(char));

	if (!*buffer)
	{
		disableBuffering();
	}

	while ((read_bytes = read(fd, *buffer + len, 1)) > 0)
	{
		if ((*buffer)[len] == '\n')
		{
			(*buffer)[len] = '\0';
			return (len);
		}

		len++;

		if (len >= *bufsize)
		{
			*bufsize *= 2;
			*buffer = realloc(*buffer, *bufsize * sizeof(char));
			if (!*buffer)
				disableBuffering();
		}
	}

	if (read_bytes == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}

	free(*buffer);
	return (-1);
}

/**
 * disableBuffering - Prints an error message
 */
void disableBuffering(void)
{
	perror("getLine");
	exit(EXIT_FAILURE);
}
