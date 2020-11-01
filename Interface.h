#pragma once
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <malloc.h>

#define MAX_HISTORY_COMMANDS 100
#define SPACE ' '
#define END_STRING '\0'

#define MAX_COMMAND_CHARACTER 30
#define MAX_COMMAND 10

extern int prevCommandSize;
extern char* previousCommands[MAX_HISTORY_COMMANDS];

void typePrompt();
void readCommand(char* command, char* params[]);
int fork(char* params[]);
void execute(char* command, char* params[], int exType);
void wait(int time);
void garbageCollector();
void openAndWriteFile(char* fileName, char* data);
char* readFile(char* fileName);
void historyStore(char* fullCommand);
bool isCommandLegit(char* command, char* params[]);
char** parseInput(int*);
void checkCommand(char* args);
extern char* previousCommand();





