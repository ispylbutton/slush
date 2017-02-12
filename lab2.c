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

void debug(char ** arguments){
  int i;
  
  for (i=0; i<16; i++){
    printf("arg %d: %s\n",i,arguments[i]);
  }
}

int cd( char* token){
  //getcwd(char *buf, size_t size);
  return chdir(token);
}

void * pwd(){
  
  printf("current directory: %s\n",get_current_dir_name());
}


int main(int argc, char* argv[]) {
 //signal(SIGINT,SIG_IGN);
 //signal(SIGQUIT,SIG_DFL);
  char buffer[8000];
  char* token;
  char* fullLine[16];
  int changedDir;
  int splitProcess;
  int i;
  char* newCommand;
  int pipefd[2];
  int ret;
  while (token!="exit"){
    fgets(buffer, 8000,stdin);
    token=strtok(buffer," \n");
    printf("token is currently %s at first strok\n", token);
    i=0;
    while ((token!=NULL)&&(i<16)) {
      fullLine[i]=token;
      i++;
      token=strtok(NULL," \n");
      printf("token is currently %s at %d strok\n", token,i);
    }
    
    if (strncmp(fullLine[0],"cd",500)==0){
      changedDir=cd(fullLine[1]);
        if (changedDir==0){
	printf("successful change\n");
      
	}
	else {
	  printf("change was not successful\n");
	}

    }
    
    else if (strncmp(fullLine[0],"pwd",500)==0){
      pwd(fullLine[1]);
      //token=strtok(NULL," ");  
    }
    else{
      pipe(pipefd);
      splitProcess=fork();
      if (splitProcess==0){
	//dup2(pipefd[1], STDOUT_FILENO); printf("line 76 check\n");
	close(pipefd[0]);
	newCommand=fullLine[0];
	char* myargv[] = {fullLine[1], '\0'};
	ret = execvp(newCommand, myargv);
	return -1;
      }
      else{
	printf("in parent\n");
      }
    }
    
    debug(fullLine);

  }
  return 0;
}
