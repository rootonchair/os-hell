#include "Interface.h"

#define FORK_ERROR "Error forking"
#define OPEN_ERROR "Error when open file"
#define DUP_ERROR "Unable to duplicate file descriptor"


int prevCommandSize = 0;
char* previousCommands[MAX_HISTORY_COMMANDS] = { NULL };
char** previousCommandTokens = NULL;

//avoid mem leak
void garbageCollector() {
	int i = 0;
	for (i = 0;; i++) {
		if (previousCommands[i] != NULL) {
			free(previousCommands[i]);
			previousCommands[i] = NULL;
		}
		else
			break;
	}

	if (previousCommandTokens == NULL)
		return;

	for (i = 0;; i++) {
		if (previousCommandTokens[i] != NULL) {
			free(previousCommandTokens[i]);
			previousCommandTokens[i] = NULL;
		}
		else
			break;
	}
}
/*
* function that display them prompt to user
*/
void typePrompt()
{
	printf("os-hell>");
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
	scanf("%[^\n]", *&command);
	getchar(); // remove '\n' in the stream
	return command;
}

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
			previousCommands[prevCommandSize][i] = (char)*(readString + i);

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
	return previousCommands[prevIndex];
}

/*
* change the previous command to te new one
* @params char*prev[] previous tokens array
* int size array size
*/

bool changePreviousCommand(char* prev[], int size)
{
	int i = 0;
	if (prev[i] == NULL || strcmp(prev[i], "") == 0) {
		printf("No history command !!!\n");
		return false;
	}
	previousCommandTokens = (char**)malloc(MAX_COMMAND * sizeof(char*));
	for (i = 0; i < size; i++) {
		previousCommandTokens[i] = prev[i];
	}

	return true;
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
	char** res = (char**)malloc(MAX_COMMAND * sizeof(char*));
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
						free(temp);
						temp = NULL;
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
	if (strcmp(command, "") == 0) {
		return NOTCOMMAND;
	}
	if (strcmp(command, "!!") == 0)
		return HISTORY;

	if (strcmp(command, "exit") == 0)
		return EXIT;

	int i = 0;
	for (i = 0;; i++) {
		if (command[i] == '\0')
			break;
		else if (command[i] == '>' || command[i] == '<')
			return REDIRECT;
		else if (command[i] == '|')
			return PIPE;
	}

	return NORMAL;
}

int getTokenLength(char** token) {
	int length = 0;
	while (token[length] != NULL) {
		length += 1;
	}
	return length;
}

void executeCommand(char** args) {
	pid_t pid;

	int tokenLength = getTokenLength(args);
	bool shouldWait = true;
	if (strcmp(args[tokenLength - 1], "&") == 0) {
		shouldWait = false;
		args[tokenLength - 1] = NULL;
	}

	if ((pid = fork()) == 0) {
		if (execvp(args[0], args) == -1) {
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid == -1) {
		// Error forking
		perror(FORK_ERROR);
		exit(EXIT_FAILURE);
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

//redirect out&input to another file
void redirect(char** tokens, int size) {
	int i = 0, fd;
	bool deleteRedirectCommand = false;

	char* filename;
	for (i = 0; i < size; i++) {
		if (deleteRedirectCommand) {
			tokens[i] = NULL;
		}
		else {
			if (strcmp(tokens[i], "<") == 0) {
				filename = tokens[i + 1];
				if ((fd = open(filename, O_RDONLY)) < 0) {
					//handle open fail
					perror(OPEN_ERROR);
					exit(EXIT_FAILURE);
				}

				if (dup2(fd, STDIN_FILENO) < 0) {
					perror(DUP_ERROR);
					exit(EXIT_FAILURE);
				}

				close(fd);
				deleteRedirectCommand = true;
				tokens[i] = NULL;
			}
			else if (strcmp(tokens[i], ">") == 0) {
				filename = tokens[i + 1];

				if ((fd = open(filename, O_WRONLY |	O_CREAT, 0644)) < 0) {
					//handle open fail
					perror(OPEN_ERROR);
					exit(EXIT_FAILURE);

				}

				if (dup2(fd, STDOUT_FILENO) < 0) {
					perror(DUP_ERROR);
					exit(EXIT_FAILURE);
				}

				close(fd);
				deleteRedirectCommand = true;
				tokens[i] = NULL;
			}
			else if (strcmp(tokens[i], ">>") == 0) {
				filename = tokens[i + 1];

				if ((fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644)) < 0) {
					//handle open fail
					perror(OPEN_ERROR);
					exit(EXIT_FAILURE);

				}

				if (dup2(fd, STDOUT_FILENO) < 0) {
					perror(DUP_ERROR);
					exit(EXIT_FAILURE);
				}

				close(fd);
				deleteRedirectCommand = true;
				tokens[i] = NULL;
			}
		}
	}
}

//function to execute redirect command
void executeRedirectCommand(char** args, int argsSize) {
	pid_t pid;
	int tokenLength = getTokenLength(args);
	bool shouldWait = true;
	if (strcmp(args[tokenLength - 1], "&") == 0) {
		shouldWait = false;
		args[tokenLength - 1] = NULL;
	}

	if ((pid = fork()) == 0) {
		redirect(args, argsSize);
		if (execvp(args[0], args) == -1) {
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid == -1) {
		// Error forking
		perror(FORK_ERROR);
		exit(EXIT_FAILURE);
	}
	else if (shouldWait) {
		wait(NULL);
	}
}

void splitPipeCommand(char** inputTokens, char*** firstCmdPtr, char*** sndCmdPtr){

	*firstCmdPtr = (char**)malloc(MAX_COMMAND * sizeof(char*));
	int firstCmdLength = 0;
	*sndCmdPtr = (char**)malloc(MAX_COMMAND * sizeof(char*));
	int sndCmdLength = 0;

	int inputTokensLength = 0;
	bool isSwitched = false;
	while(inputTokens[inputTokensLength] != NULL){
		if (strcmp(inputTokens[inputTokensLength], "|") == 0){
			isSwitched = true;
		}
		else {
			char* token = inputTokens[inputTokensLength];
			if(!isSwitched){
				(*firstCmdPtr)[firstCmdLength] = token;
				firstCmdLength += 1;
			}
			else {
				(*sndCmdPtr)[sndCmdLength] = token;
				sndCmdLength += 1;
			}
		}

		inputTokensLength += 1;
	}

	(*firstCmdPtr)[firstCmdLength] = NULL;
	(*sndCmdPtr)[sndCmdLength] = NULL;
}

void executePipesCommand(char** args, int argsSize) {
	pid_t pid;
	int fd[2];

	if ((pipe(fd) < 0)) {
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}

	if ((pid = fork()) < 0) {
		perror(FORK_ERROR);
		exit(EXIT_FAILURE);
	}

	char** firstCmd;
	char** sndCmd;

	splitPipeCommand(args, &firstCmd, &sndCmd);

	//in child process
	if (pid == 0)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		//close read descriptor
		close(fd[READ_END]);
		//close write descriptor	
		close(fd[WRITE_END]);
		if (execvp(firstCmd[0], firstCmd) < 0)
			perror(firstCmd[0]);
		exit(EXIT_FAILURE);
	}
	else
	{ //in parent process
		if ((pid = fork()) < 0) {
			perror(FORK_ERROR);
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			dup2(fd[READ_END], STDIN_FILENO);
			close(fd[WRITE_END]);
			close(fd[READ_END]);
			if (execvp(sndCmd[0], sndCmd) < 0)
				perror(sndCmd[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			// wait for the child processes to finish
			// in case both of them all failed
			wait(NULL);
			wait(NULL);
			// Only free the pointers
			free(firstCmd);
			free(sndCmd);
		}
	}

}
