#include "main.h"

/**
 * printErrorMessage - Prints an error message to stderr
 * @cmd: First argument
 * @msg: Error message
 * @line_num: Line number to track error
 * Return: Always 0 (Success)
 */
void printErrorMessage(const char *cmd, const char *msg, int line_num)
{
	const char *shell_name = "hsh";
	const char *separator = ": ";
	char line_number_str[16];
	unsigned long int i = 0;
	int j, n = line_num;
	size_t shell_name_len = strlen(shell_name);
	size_t separator_len = strlen(separator);

	write(STDERR_FILENO, shell_name, shell_name_len);
	write(STDERR_FILENO, separator, separator_len);

	if (n == 0)
	{
		line_number_str[i++] = '0';
	}
	else
	{
		while (n > 0 && i < sizeof(line_number_str) - 1)
		{
			line_number_str[i++] = '0' + (n % 10);
			n /= 10;
		}
	}
	for (j = i - 1; j >= 0; j--)
	{
		write(STDERR_FILENO, &line_number_str[j], 1);
	}

	write(STDERR_FILENO, separator, separator_len);
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, separator, separator_len);
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}


/**
 * getErrorDirectory - Creates an error message for cd command
 * @args: Arguments
 * Return: Pointer to the error message
 */
char *getErrorDirectory(char **args)
{
	char *error_message = (char *)malloc(100 * sizeof(char));

	if (error_message == NULL)
	{
		return (NULL);
	}

	strcpy(error_message, " can 't ");
	strcat(error_message, "  ");
	strcat(error_message, args[0]);
	strcat(error_message, "  to ");
	strcat(error_message, args[1]);

	return (error_message);
}
