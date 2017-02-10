//Nick Vilimek

#include <stdio.h>
#include <string.h>

int main ( int argc, char* argv[] ){
  char* cmd;
  char buffer[200];
  char* strippedNewline;
  
  fgets(buffer,200,stdin);
  
  strippedNewline = strtok(buffer,"\n");
  
  while(cmd != NULL){
    printf("%s\n", cmd);
    cmd = strtok(NULL,",");
  }
  /*
  int max_args = 15;
  int max_argv_size = max_args + 2;
  char* cmd;
  char* my_argv[max_argv_size];
  char* remainingArgv;
  
  cmd = strtok(strippedNewline," ");
  my_argv[0] = cmd;
  
  int i;
  for(i=1;i<max_argv_size;i++){
    remainingArgv = strtok(NULL," ");
    if(remainingArgv == NULL){ 
      my_argv[i] = '\0';
      break; 
    }
    my_argv[i] = remainingArgv;
    
  }
  
  execvp( cmd, my_argv );
  */
  return 0;
}
 
 
