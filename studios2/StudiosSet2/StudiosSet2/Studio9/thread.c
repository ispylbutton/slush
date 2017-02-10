#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFSIZE 64

struct struct_1{
  int arg1;
  char arg2[BUFSIZE];
  int ret;
};

static void * thread_entry(void *args){
  struct struct_1* arg_ptr = (struct struct_1*) args;
  
  printf("thread arg2: %s\n", arg_ptr->arg2);
  arg_ptr->ret = 4;
  
  return NULL;
  
}


int main(int argc,char *argv[]){
  
  int num_threads = 5;
  pthread_t thread[num_threads];
  struct struct_1 args[num_threads];
  int i;
  for( i = 0; i < num_threads; i++ ){
    //Write into the arg2 
    snprintf(args[i].arg2, BUFSIZE, "This is thread %d", i);
    //Create
    if((pthread_create(&(thread[i]),NULL,&thread_entry,&(args[i])))!=0){
      printf("Error in creating thread");
      exit(1);
    }
    //Join
    if((pthread_join(thread[i],NULL))!=0){
      printf("Error in joining thread");
      exit(1);
    }
  }
  return 0;
  
}