#include "main.h"  /* Include main header file */

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: Always 0 (Success)
 */
int main(int argc __attribute__((unused)), char **argv)
{
	bool interactive = isatty(STDIN_FILENO);
	const char *shellPrompt = interactive ? "$ " : "";
	size_t buffer_size = 0;
	ssize_t line_length;
	int line_num = 1;
	char *input_line = NULL;  /* Declare a separate variable for input line */
	char **cmd;

	while (true)
	{
		/* Print shell prompt if in interactive mode */
		if (interactive)
		{
			write(STDOUT_FILENO, shellPrompt, strlen(shellPrompt));
			fflush(stdout);
		}

		/* Read input line */
		/* Use input_line variable */
		line_length = getline(&input_line, &buffer_size, stdin);

		if (line_length == -1)
		{
			/* Check for end of input */
			if (feof(stdin))
			{
				exit(EXIT_SUCCESS);
			}
			break;
		}

		/* Skip empty lines */
		if (line_length == 1 && input_line[0] == '\n')
			continue;

		/* executeCommand commands */
		cmd = argv;
		while (*cmd != NULL)
		{
			executeCommand(*cmd, line_num);
			cmd++;
		}

		/* Free arguments */
		freeArguments(argv);

		line_num++;
	}

	free(input_line);  /* Free the input line buffer */

	return 0;
}
