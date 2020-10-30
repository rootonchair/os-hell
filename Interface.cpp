#include "Interface.h"


int prevCommandSize = 0 ;
char *previousCommands[MAX_HISTORY_COMMANDS] = { nullptr };

/*
* function that display them prompt to user
*/
void typePrompt()
{
}
/*
* function read user input and store in
*
* @param command Store the command from user input
* @param params Store the parameters from user input
*/
void readCommand(char* command, char* params[])
{
}

/*
* function fork the command from users
*
* @param params Some params, still not sure if needed
* @return int value whether the fork success
*/
int fork(char* params[])
{
	int result = 0;


	return result;
}

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
* function wait for the child Thread
*
* @param time maybe something else, just guessing
*/
void wait(int time)
{
}

/*
* function collect garbage
*
*/
void garbageCollector()
{
}
/*
* function open a file and write data in
*
* @param fileName name of the File
* @param data the text data to write in file
*/
void openAndWriteFile(char* fileName, char* data)
{

}


/*
* function read the data from txt file
*
* @param fileName name of file
* @return char* data that read from file
*/
char* readFile(char* fileName)
{
	return nullptr;
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
	
	if (readString == nullptr)
		return;

	int i = 0;
	
	for (i = 0; readString[i] != '\0'; i++) {
		//if the command is longer than expected -> supply more
		if (i > MAX_COMMAND_CHARACTER) {
			char* temp = nullptr;
			do {
				temp = (char*)realloc(previousCommands[prevCommandSize], (i + 1) * sizeof(char));
			} while (temp != nullptr);
			previousCommands[prevCommandSize] = temp;
		}
		previousCommands[prevCommandSize][i] = readString[i];
	}
	previousCommands[prevCommandSize][i] = (char)'\0';
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
char** parseInput(int& arrSize)
{
	char readString[MAX_COMMAND_CHARACTER], *temp = new char[MAX_COMMAND_CHARACTER];
	char* res[MAX_COMMAND];

	int i = 0, j = 0;
	arrSize = 0;

	//read the user input
	scanf("%[^\n]", readString);
	getchar();

	//call checkCommand func
	checkCommand(readString);

	//add to history
	addToHistory(readString);
		 
	//make tokens
	while (1) {
		if (readString[i] == SPACE || readString[i] == END_STRING) {
			temp[j] = '\0';
			res[arrSize] = temp;

			arrSize++;
			j = 0;
			temp = new char[MAX_COMMAND_CHARACTER];
		}
		else {
			temp[j] = readString[i];
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




