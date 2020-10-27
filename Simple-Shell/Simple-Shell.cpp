#include <stdio.h>
#include "Interface.h"
	
#define MAX_LINE 80 /* The maximum length command */
#define CUTTING_WORD " \n" // for dividing string
#define ENDING_WORD "done" // Program end word
#define PARRAL		
#define RESET 0

int main(void)
{
	char* args[MAX_LINE / 2 + 1]; /* command line arguments */
	int shouldRun = 1; /* flag to determine when to exit program */
	while (shouldRun) {
		printf("osh>");
		fflush(stdout);
		/**	
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) parent will invoke wait() unless command included &
		*/
	}
	return 0;
}