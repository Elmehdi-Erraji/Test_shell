#include "main.h"

/**
 * handleSIGINT - Signal handler for SIGINT (CTRL + C)
 * @sigNum: Signal number
 */
void handleSIGINT(int sigNum)
{
	(void)sigNum;
	write(STDOUT_FILENO, "\n", 1);
	signal(SIGINT, handleSIGINT);
}
