#include "Interface.h"
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


