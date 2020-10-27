#pragma once
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
