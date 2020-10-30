#include<stdio.h>
#include<unistd.h>

void executeCommand(char** args, bool shouldWait){
  if (fork()==0){
    execvp(args[0], args);
  }
  else if (shouldWait){
    wait()
  }
}

int main(){
  printf("Hello World\n");
  char* args[2];
  args[0] = "ls";
  args[1] = NULL;
  execvp(args[0], args);
  return 0;
}
