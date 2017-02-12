#include <pthread.h>
#include<stdio.h>
#include<unistd.h>


int race;

void adder() {
  race+=2000000;
}
void subtractor() {
  race-=2000000;
}


int main (int argc, char argv[]){
  
  adder();
  subtractor();
  printf("%d\n", race);
  
  return 0;
}