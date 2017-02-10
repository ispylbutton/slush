//Nick Vilimek

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main ( int argc, char* argv[] ){
   pid_t prog1,prog2;
   int pipefd[2];
   
   pipe(pipefd);
   
   char* cmd;
   int ret;

  prog1 = fork();
  
  if (prog1 == 0) {
    
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[0]);
    
    printf("Program1\n");
    cmd = "./Program1";
    char* myargv[] = {"Program1", '\0'};
    ret = execvp( cmd, myargv );
    return -1;
    
  } 
  
  prog2 = fork();
  
  if(prog2 == 0){
      
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[1]);
    
    printf("Program2\n");
    cmd = "./Program2";
    char* myargv[] = {"Program2", '\0'};
    ret = execvp( cmd, myargv );
    return -1;
  }
  
  close(pipefd[0]);
  close(pipefd[1]);
  
  waitpid(prog1,NULL,0);
  waitpid(prog2,NULL,0);
      
  printf("Parent returned\n");
  
  return 0;
}