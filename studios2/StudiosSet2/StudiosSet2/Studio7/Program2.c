//Nick Vilimek

#include <stdio.h>
#include <string.h>

int main ( int argc, char* argv[] ){
  
  char buffer[200];
  
  while(1){
    if(fgets(buffer,200,stdin)==NULL){
      break;
    }
    printf("Program 2 got: %s",buffer);
  }
  
  return 0;
}
 
 
 
