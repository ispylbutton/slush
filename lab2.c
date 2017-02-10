/*Spawn new processes with the fork() and execvp() system calls
Wait for child processes with the wait() system call
Perform complex input parsing in C
Pipe data between processes
Perform basic signal handling*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char* argv[]) {
 //signal(SIGINT,SIG_IGN);
 //signal(SIGQUIT,);
 
char buffer[200];
char* firstToken;
while (firstToken!="exit"){
fgets(buffer, 200,stdin);
firstToken=strtok(buffer,",");
//while firstToken!=
while (firstToken!=NULL) {
  printf("%s\n", firstToken);

  firstToken=strtok(NULL,",");
}
}
  return 0;
}