#ifndef MAIN_Hi
#define MAIN_H
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

/* -- standard library functions -- */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <ctype.h>

/**-- Global environment -- */
extern char **environ;
extern int exit_status;


/**-- MACROS var envirement -- **/
#define MAX_ARGS 128
#define MAX_PATH_LENGTH 256



/**
 * --struct LinkedPath - This is a linked list containing
 * ----Each diretory in the path
 * @dir:  a directory Path
 * @next:   a pointer to the next director
 * *
 */
typedef struct LinkedPath
{
	char *dir;
	struct LinkedPath *next;
} LinkedPath;

/**
 * struct Alias This is a linked list contaning
 * ---------------Each diretory in path
 *
 * @maincommand:  the main command
 * @newcommand:  a new command
 * @next:a  pointer to the next Alias
 */
typedef struct Alias
{
	char *mainCmd;
	char *newCmd;
	struct Alias *next;
} Alias;
extern Alias *Aliaslist;

/* -- memory_freeing_functions --*/
void freeEnvironment(void);
void freeArguments(char **args);
void freePath(LinkedPath *path);

/**-- Alias_handler_functions --*/
int setAlias(char **args);
int createKeyValuePair(Alias **AliasList, char *args, char *equals);
Alias *addAlias(Alias **head, char *newCmd, char *mainCmd);
int printAliasList(Alias *head);
char *checkAlias(char *newCmd);
int executeCommandAlias(char *mainCmd, char **args);
Alias *getAliasList(void);

/**--  the Environ_functions-- */
int setEnvironmentVariable(const char *name, const char *value, int overwrite);
int showEnvironment(void);
int checkPath(char **args);
char *getEnvironmentVariable(const char *name);
char *getDiretory();
int unsetEnvironmentVariable(char **args);
LinkedPath *linkPath(void);

/** the_executeCommand_Functions */
int setEnvironmentVariableVariable(const char *name, const char *value, int overwrite);
int showEnvironment(void);
int checkPath(char **args);
char *getDirectory(void);
int unsetEnvironmentVariableVariable(char **args);
LinkedPath *linkPath(void);

int executeCommand(char *command, int lineNum);
int executeCommandWithPath(char **args);
ssize_t getLine(char **buffer, size_t *bufsize, int fd);
int changeDirectory(char **args, int lineNum);
int echoCommand(char **args);
int runChildProcess(char **args);
int runParentProcess(void);
int getExitStatus(void);

char *stringTokenize(char *command, const char *delim);
int tokenizeCommand(char *command, char **args);
int isBuiltInCommand(char **args, int lineNum);
int isBuiltInCommand2(char **args, int lineNum);
int stringLength(const char *s);
int compareStrings(const char *s1, const char *s2);
char *findFirstOccurrence(const char *s, const char c);
char *duplicateString(const char *str);
int compareStringsWithLimit(const char *s1, const char *s2, size_t n);
void printErrorMessage(const char *command, const char *message, int lineNum);
char *integerToString(int value);
char *getErrorDirectory(char **args);
char *concatenateStrings(char *dest, const char *src);
char *copyString(char *dest, const char *src);
int echoParentProcessID(int printedChars);
int echoExit(int printedChars);
int echoEnvironmentVariable(int printedChars, char **args, int i);
void disableBuffering(void);
int exitShell(char **args);

#endif /* MAIN_H */
