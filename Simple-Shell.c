#include "Interface.h"

#define PARRAL 23
#define RESET 0


int main(void)
{
	bool shouldRun = true;
	char** parsedInput = NULL;
	char* prevCom = NULL;
	int arraySize = 0;
	char** prevCommandTokens = NULL;
	bool executePrevCommand = false;
	enum CommandType type = NOTCOMMAND;

	char* input = NULL;
	while (shouldRun) {
		/**
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) parent will invoke wait() unless command included &
		*/

		//avoid mem leak
		free(input);

		if (!executePrevCommand){
			typePrompt();
			//read
			input = readCommand();

			//check command return ENUM
			type = checkCommand(input);

			//parse the input and assign to previos command
			if (type != HISTORY && type != EXIT && type != NOTCOMMAND) {
				parsedInput = parseInput(input, &arraySize);
				changePreviousCommand(parsedInput, arraySize);
				addToHistory(input);
				executePrevCommand = false;
			}
		} else {
			parsedInput = prevCommandTokens;
			prevCommandTokens = NULL;
			input = getPreviousCommand();
			type = checkCommand(input);
			executePrevCommand = false;
		}
		
		
		switch (type) {
		case NORMAL:
			executeCommand(parsedInput);
			break;
		case HISTORY:
			prevCommandTokens = getPreviousCommandTokens();
			executePrevCommand = true;	
			break;
		case EXIT:
			exit(0);
			break;
		case PIPE:
			break;
		case REDIRECT:
			executeRedirectCommand(parsedInput,arraySize);
			break;
		case NOTCOMMAND:
			break;
		default:
			break;
		}


	}
	return 0;
}

