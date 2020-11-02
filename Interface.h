#pragma once
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <malloc.h>

#define MAX_HISTORY_COMMANDS 100
#define SPACE ' '
#define END_STRING '\0'

#define MAX_COMMAND_CHARACTER 80
#define MAX_COMMAND 30

extern enum CommandType
{
	PIPE, NORMAL, EXIT, REDIRECT, HISTORY,NOTCOMMAND
};


extern int prevCommandSize;
extern char* previousCommands[MAX_HISTORY_COMMANDS];
extern char* previousCommand[MAX_COMMAND];

void typePrompt();
char *readCommand();
int fork(char* params[]);
void execute(char* command, char* params[], int exType);
void wait(int time);
void garbageCollector();
void openAndWriteFile(char* fileName, char* data);
char* readFile(char* fileName);
void historyStore(char* fullCommand);
bool isCommandLegit(char* command, char* params[]);
char** parseInput(char*,int*);
enum CommandType checkCommand(char* command);
extern char* getPreviousCommand();
extern void changePreviousCommand(char* prev[], int size);




