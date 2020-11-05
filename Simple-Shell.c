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
	bool isPrevComNotNull = false;

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
				isPrevComNotNull = changePreviousCommand(parsedInput, arraySize);
				addToHistory(input);
				executePrevCommand = false;
			}
		} else {
			parsedInput = prevCommandTokens;
			prevCommandTokens = NULL;
			input = getPreviousCommand();
			//printf("%s",input);
			type = checkCommand(input);
			executePrevCommand = false;
		}
		
		
		switch (type) {
		case NORMAL:
			executeCommand(parsedInput);
			break;
		case HISTORY:
			prevCommandTokens = getPreviousCommandTokens();
			if (isPrevComNotNull) {
				isPrevComNotNull = false;
				executePrevCommand = true;
			} else {
				fprintf(stderr,"No history command !!!\n");
			}
			break;
		case EXIT:
			garbageCollector();
			exit(0);
			break;
		case PIPE:
			executePipesCommand(parsedInput,arraySize);
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
	garbageCollector();
	return 0;
}

