#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MAX_HISTORY_COMMANDS 100
#define SPACE ' '
#define END_STRING '\0'

const int MAX_COMMAND_CHARACTER = 30;
const int MAX_COMMAND = 10;

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
char** parseInput(int&);
void checkCommand(char* args);
extern char* previousCommand();




