#include "Interface.h"
	
#define PARRAL 23
#define RESET 0


int main(void)
{
	bool shouldRun = true;
	char** parsedInput;
	char* prevCom = NULL;
	int arraySize = 0;

	char* input = (char*)malloc(MAX_COMMAND_CHARACTER * sizeof(char));
	while (shouldRun) {
		typePrompt();
		/**	
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) parent will invoke wait() unless command included &
		*/
		//read
		input = readCommand();
		
		//check command return ENUM
		enum CommandTye type = checkCommand(input);

		//parse the input and assign to previos command
		if (type != HISTORY && type != EXIT && type != NOTCOMMAND) {
			parsedInput = parseInput(input, &arraySize);
			changePreviousCommand(parsedInput, arraySize);
		}

		switch (type) {
		case NORMAL:
			break;
		case HISTORY:
			break;
		case EXIT:
			exit(0);
			break;
		case PIPE:
			break;
		case REDIRECT:
			break;
		case NOTCOMMAND:
			break;
		default:
			break;
		}
		

	}
	return 0;
}