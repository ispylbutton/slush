#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void debug(char *** arguments){
  int i;
  int j;
  while (arguments[i][j]!=NULL)
  {
    printf("arg %d %d: %s\n",i,j,arguments[i][j]);
  }
}

int cd( char* ret){
  //getcwd(char *buf, size_t size);
  return chdir(ret);
}

void * pwd(){
  
  printf("current directory: %s\n",get_current_dir_name());
}
/*
void (fork_and_exec(char* cmd))
{
  char* newCommand;//only fork and exec
  int splitProcess;//only fork and exec
  int pipefd[2];//only fork and exec
  int retVal;//only fork and exec
      pipe(pipefd);
      splitProcess=fork();
      if (splitProcess==0){
	//dup2(pipefd[1], STDOUT_FILENO); printf("line 76 check\n");
	close(pipefd[0]);
	newCommand=cmd[0];
	char* myargv[] = {cmd[1], '\0'};
	ret = execvp(newCommand, myargv);
	return -1;
      }
      else{
	printf("in parent\n");
      }
}
*/

 
int main(int argc, char* argv[]) {
  char buffer[8000];
  char * ret; //token
  char * commands [16];//fullLine
  int changedDir;
  int l,q;
    char* newCommand;//only fork and exec
  int splitProcess;//only fork and exec
  int pipefd[2];//only fork and exec
  int retVal;//only fork and exec
  while (ret!="exit") {
    fgets(buffer,8000,stdin);
    ret=strtok(buffer, "\n(");
    printf("ret is currently %s at first strok\n", ret);
    l=0;
    while ((ret!=NULL)&&(l<16))
    {
      commands[l]=ret;
      l++;
      ret=strtok(NULL,"\n(");
      printf("ret is currently %s at %d strok\n", ret,l);
    }
    
    if (strncmp(commands[0],"cd",500)==0){
      changedDir=cd(commands[1]);
        if (changedDir==0){
	printf("successful change\n");
      
	}
	else {
	  printf("change was not successful\n");
	}
    }   
    else if (strncmp(commands[0],"pwd",500)==0){
      pwd(commands[1]);
      //ret=strtok(NULL," ");  
    }
    else{
      pipe(pipefd);
      while (strncmp(commands[q],"/0",500)==0){
	ret=strtok(NULL," ");
	splitProcess=fork();
	if (splitProcess==0){
	  //dup2(pipefd[1], STDOUT_FILENO); printf("line 76 check\n");
	  close(pipefd[0]);
	  //for 
	  newCommand=commands[0];
	  char* myargv[] = {commands[1], '\0'};
	  retVal = execvp(newCommand, myargv);
	  return -1;
	}
	else{
	  printf("in parent\n");
	}
      }
    }
    
    
    debug(commands);

  }
  return 0;
}//last bracket






//ret=strtok(




