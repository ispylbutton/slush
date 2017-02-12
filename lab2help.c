/*Spawn new processes with the fork() and execvp() system calls
Wait for child processes with the wait() system call
Perform complex input parsing in C
Pipe data between processes
Perform basic signal handling*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int cd( char* token){
  return chdir(token);
}

void * pwd(char* token){
  printf("%s",token);
}
       //int fchdir(int fd);
       
       //char *getcwd(char *buf, size_t size);

       //char *getwd(char *buf);

       //char *get_current_dir_name(void);









int main(int argc, char* argv[]) {
 //signal(SIGINT,SIG_IGN);
 //signal(SIGQUIT,SIG_DFL);
 
char buffer[200];
char* token;
char* dirName;
char* fullLine;
int i=0;
while (token!="exit"){
    printf("slush | ");
    fgets(buffer, 200,stdin);
    token=strtok(buffer," ");

while (token!=NULL) {
  fullLine[i]=token;
  i++;
}
  //printf("%s\n", firstToken);
  if (fullLine[0]=="cd"){
    int changedDir=cd(fullLine[2]);
  }
  else if (fullLine[0]=="pwd"){
    pwd(fullLine[2]);
    token=strtok(NULL," ");
  }
}

  return 0;
}