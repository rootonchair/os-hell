#include "Interface.h"


int prevCommandSize = 0 ;
char *previousCommands[MAX_HISTORY_COMMANDS] = { NULL };


/*
* function execute user command
*
* @param command Store the command from user input
* @param params Store the parameters from user input
* @param exType execute type (execvp, execvt,...)
*/
void execute(char* command, char* params[], int exType)
{
}

/*
* function store the previous command
*
* @param fullCommand The previous command that user type in
*/
void historyStore(char* fullCommand)
{
}

/*
* function check the legitement of user input
*
* @param fullCommand The command user type in
* @return bool value if legit or not
*/
bool isCommandLegit(char* command, char* params[])
{
	bool result = false;


	return result;
}
	
void addToHistory(char *readString) {	
	//supply the space for array
	previousCommands[prevCommandSize] = (char*)malloc(sizeof(char));
	
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

char* previousCommand()
{
	int prevIndex = prevCommandSize - 1;
	return previousCommands[prevCommandSize-1];
}


/*
* read and parse the Input
*
* @param arrSize size of the array**
* @return char** return commands array
*/
char** parseInput(int *arrSize)
{
	char *readString = (char*)malloc(MAX_COMMAND_CHARACTER*sizeof(char));
	char* res[MAX_COMMAND] = { NULL };

	int i = 0, j = 0;
	*arrSize = 0;

	//read the user input
	if (scanf("%[^\n]", *&readString) == NULL)
		return;
	if (getchar());
	

	//call checkCommand func
	checkCommand(readString);

	//add to history
	addToHistory(readString);

		 
	//make tokens
	while (readString!=NULL) {
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
			if (res[*arrSize]!=NULL)
				res[*arrSize][j] = '\0';
			*arrSize = *arrSize+1;
			j = 0;
		}
		else {
			if (j > MAX_COMMAND_CHARACTER) {
				do {
					char *temp = (char*)realloc(res[*arrSize],(j+1) * sizeof(char));
					if (temp != NULL) {
						res[*arrSize] = temp;
						//avoid mem leak
						temp = NULL;
						free(temp);
						break;
					}
				} while (res[*arrSize]==NULL); //suply fail -> resuply
			}
			
			if (res[*arrSize]!=NULL)
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

void checkCommand(char* args)
{
	//do something
}
