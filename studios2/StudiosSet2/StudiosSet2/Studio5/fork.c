//Nick Vilimek

#include <stdio.h>
#include <string.h>

int main ( int argc, char* argv[] ){
  
  int child_PID = fork();
  if(child_PID==0){
    sleep(3);
    printf("Child %d\n",getpid());
    
    char* child_argv[] = {"ls", "-l", NULL};
    char* child_prog = child_argv[0];
    execvp(child_prog,child_argv);
    //execvp(argv[1],argv);
    
  }else {
   waitpid( child_PID, NULL, 0 );
    printf("Parent %d\n",getpid());
  }
  
  return 0;
}
 
