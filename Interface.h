#pragma once
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_HISTORY_COMMANDS 100
#define SPACE ' '
#define END_STRING '\0'

#define MAX_COMMAND_CHARACTER 80
#define MAX_COMMAND 30

#define WRITE_END 1
#define READ_END 0

static enum CommandType
{
	PIPE, NORMAL, EXIT, REDIRECT, HISTORY, NOTCOMMAND
};


extern int prevCommandSize;
extern char* previousCommands[MAX_HISTORY_COMMANDS];
extern char** previousCommandTokens;

void typePrompt();
char* readCommand();
void executeCommand(char** args);
//void execute(char* command, char* params[], int exType);
//void wait(int time);
void garbageCollector();
//void openAndWriteFile(char* fileName, char* data);
//char* readFile(char* fileName);
//void historyStore(char* fullCommand);
//bool isCommandLegit(char* command, char* params[]);

char** parseInput(char*, int*);
enum CommandType checkCommand(char* command);
void addToHistory(char* readString);
extern char* getPreviousCommand();
extern bool changePreviousCommand(char* prev[], int size);
extern char** getPreviousCommandTokens();
void redirect(char **tokens,int);
void executeRedirectCommand(char** args,int argsSize);
void executePipesCommand(char **args,int argsSize);




