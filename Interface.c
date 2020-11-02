#include "Interface.h"


int prevCommandSize = 0;
char* previousCommands[MAX_HISTORY_COMMANDS] = { NULL };
char* previousCommandTokens[MAX_COMMAND] = { NULL };

/*
* function that display them prompt to user
*/
void typePrompt()
{
	printf("osh>");
	fflush(stdout);
}

/*
* function read user input
* @return the char array of user input
*/
char* readCommand()
{
	//init memory
	char* command = (char*)malloc(MAX_COMMAND_CHARACTER * sizeof(char));

	//read the user input
	if (scanf("%[^\n]", *&command) == 0)
		return NULL;
	if (getchar());
	return command;
}


/*
* function execute user command
*
* @param command Store the command from user input
* @param params Store the parameters from user input
* @param exType execute type (execvp, execvt,...)
*/


/*
* function wait for the child Thread
*
* @param time maybe something else, just guessing
*/


/*
* function collect garbage
*
*/


/*
* function open a file and write data in
*
* @param fileName name of the File
* @param data the text data to write in file
*/



/*
* function read the data from txt file
*
* @param fileName name of file
* @return char* data that read from file
*/


/*
* function store the previous command
*
* @param fullCommand The previous command that user type in
*/



/*
* function check the legitement of user input
*
* @param fullCommand The command user type in
* @return bool value if legit or not
*/



void addToHistory(char* readString) {
	//supply the space for array
	do {
		previousCommands[prevCommandSize] = (char*)malloc(sizeof(char));
	} while (previousCommands[prevCommandSize] == NULL);

	if (readString == NULL)
		return;

	int i = 0;

	for (i = 0;; i++) {
		//if the command is longer than expected -> supply more
		if (i > MAX_COMMAND_CHARACTER) {
			char* temp = NULL;
			do {
				temp = (char*)realloc(previousCommands[prevCommandSize], (i + 1) * sizeof(char));
			} while (temp != NULL);
			previousCommands[prevCommandSize] = temp;
		}
		if (previousCommands[prevCommandSize] != NULL)
			previousCommands[prevCommandSize][i] = (char)readString[i];

		if (readString[i] == '\0') {
			if (previousCommands[prevCommandSize] != NULL)
				previousCommands[prevCommandSize][i] = (char)'\0';

			break;
		}
	}
	prevCommandSize++;
}

/*
* Get the previous command
* @params
*/

char* getPreviousCommand()
{
	int prevIndex = prevCommandSize - 1;
	return previousCommands[prevCommandSize - 1];
}

/*
* change the previous command to te new one
* @params char*prev[] previous tokens array
* int size array size
*/

void changePreviousCommand(char* prev[], int size)
{
	int i = 0;
	for (i = 0; i < size; i++) {
		previousCommandTokens[i] = (char)malloc(MAX_COMMAND_CHARACTER * sizeof(char));
		previousCommandTokens[i] = prev[i];
	}

	prev = NULL;
	free(prev);
}


/*
* parse the Input into tokens
*
* @param arrSize size of the array**
* @return char** return commands array
*/
char** parseInput(char* readString, int* arrSize)
{
	//init 
	char** res = (char*)malloc(MAX_COMMAND * sizeof(char*));
	int i = 0, j = 0;
	*arrSize = 0;

	//make tokens
	while (readString != NULL) {
		//initial the array
		if (j == 0) {
			char* temp = NULL;
			do {
				temp = (char*)malloc(MAX_COMMAND_CHARACTER * sizeof(char));
				if (temp != NULL) {
					res[*arrSize] = temp;
					//avoid mem leak
					temp = NULL;
					free(temp);
					break;
				}
			} while (temp == NULL);
		}

		if (readString[i] == SPACE || readString[i] == END_STRING) {
			if (res[*arrSize] != NULL)
				res[*arrSize][j] = '\0';
			*arrSize = *arrSize + 1;
			j = 0;
		}
		else {
			if (j > MAX_COMMAND_CHARACTER) {
				do {
					char* temp = (char*)realloc(res[*arrSize], (j + 1) * sizeof(char));
					if (temp != NULL) {
						res[*arrSize] = temp;
						//avoid mem leak
						temp = NULL;
						free(temp);
						break;
					}
				} while (res[*arrSize] == NULL); //suply fail -> resuply
			}

			if (res[*arrSize] != NULL)
				res[*arrSize][j] = readString[i];

			j++;
		}

		if (readString[i] == END_STRING) {
			break;
		}

		i++;
	}

	return res;
}

/*
* Check the type of the input command
* @param char* the Command user input
* @param int size of the command
* @return ENUM type of the command
*/
enum CommandType checkCommand(char* command)
{
	if (strcmp(command, "\n") == 0) {
		return NOTCOMMAND;
	}
	if (strcmp(command, "!!") == 0)
		return HISTORY;

	if (strcmp(command, "exit") == 0)
		return EXIT;

	return NORMAL;
}

// execute command by Vinh

void executeCommand(char** args, bool shouldWait) {
	if (fork() == 0) {
		execvp(args[0], args);
	}
	else if (shouldWait) {
		wait(NULL);
	}
}

// return previous command in tokens
char** getPreviousCommandTokens()
{
	return previousCommandTokens;
}




