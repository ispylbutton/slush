#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


void sigHandler(int signal)
{
  if (signal==SIGINT)
  {
    
  }
}


void report_and_exit(char* errorType)
{
  perror(errorType);
  exit(-1);
}

void debug(char * arguments[100][17]){
  int i;
  int j;
  i=0;
  j=0;
  while (arguments[i]!=NULL&&arguments[i][j]!=NULL)
  {
    while (arguments[i][j]!=NULL)
    {
      printf("arg %d %d: %s\n",i,j,arguments[i][j]);
      j++;
    }
    i++;
    j=0;
  }
}

int cd( char* ret){
  return chdir(ret);
}

void pwd(){
  printf("current directory: %s\n",get_current_dir_name());
}

int isChild=0;

void changeFd(int oldfd, int newfd) 
{
  if( dup2(oldfd, newfd) == -1 )
    report_and_exit("Error changing FDs");
  /*
  if (oldfd!=newfd)
  {
    if (dup2(oldfd, newfd)!=-1)
    {
      if (close(oldfd)==-1)
      {
	perror("closing error");
      }
      else 
      {
	report_and_exit("Error changing Fds");
	
      }
    }
  }
  */
}

void fork_and_exec(char* cmdLine[100][17], int pos, int oldfd)
{
     
    if (pos == 1)
    {
      int ret = fork();
      if( ret == 0 ){
	execvp(cmdLine[0][0], cmdLine[0]);
	report_and_exit("error executing final command");
      }
      waitpid(ret, NULL, 0);
      return;
    }
  
  oldfd = 0;
  
  int cmd = pos-1;
  while( cmd >= 0 ){
    printf("executing %s\n", cmdLine[cmd][0]);
    int newfd[2];
    if (cmd!=0)
    {
      
      if (pipe(newfd)==-1)
      {
	report_and_exit("Piping error");
      }
    }
      switch(fork())
      {
      default:
	if (close(newfd[1])==-1)
	{
	  perror("Error closing newfd");
	}
	if( oldfd != 0 )
	{
	if (close(oldfd)==-1)
	{
	  perror("error closing oldfd");
	}
	
	}
	oldfd=newfd[0];
	break;

      case 0:
	isChild=1;
	if (cmd==0)
	{
	  changeFd(oldfd, STDIN_FILENO);
	  //changeFd(newfd[1],STDOUT_FILENO);
	  execvp(cmdLine[cmd][0],cmdLine[cmd]);
	  report_and_exit("error executing current command");
	}
	else if (cmd==(pos-1))
	{
	  changeFd(newfd[1],STDOUT_FILENO);
	  execvp(cmdLine[cmd][0],cmdLine[cmd]);
	  report_and_exit("error executing current command");
	}
	//ifcmd=0 leftmost
	//if cmd=pos-1 rightmost
	else{
	  if (close(newfd[0])==-1)
	  {
	    report_and_exit("error closing newfd");
	  }
	
	  changeFd(oldfd, STDIN_FILENO);
	  changeFd(newfd[1],STDOUT_FILENO);
	  execvp(cmdLine[cmd][0],cmdLine[cmd]);
	  report_and_exit("error executing current command");
	  }
	  break;
      case -1:
	report_and_exit("error with forking");
    }
  
    cmd--;
  }
  
}



int main (int argc, char * argv[]) {
  signal(SIGINT,sigHandler);
  char buffer[8000];
  int delim_count;
  delim_count=15;
  char * ret;
  int l,q,r,x,count,i;
  char* commands[100][delim_count+2];
  char* commandSep[17];
  int changedDir;
  int length;
  char * copy;
  
  while (ret!="exit") {
    count=0;
    fgets(buffer,8000,stdin);
    
    /*
    char*tmp;
    for (tmp=buffer; *tmp; tmp++) 
    {
      delim_count+=*tmp=='(';
    }
   */
    //commands=malloc(sizeof(char***[delim_count+2]));
    //commandSep=malloc(sizeof(char**)*17);
     for (count=0; count<100; count++)
     {
     for (i=0;i<delim_count+2; i++)
      {
	commands[count][i]=NULL;
      }
     }
    //count+=2;
    ret=strtok(buffer, "\n(");
    printf("ret is currently %s at first strok\n", ret);
    l=0;
    while ((ret!=NULL))
    {
      commandSep[l]=ret;
      
      ret=strtok(NULL,"\n(");
      printf("ret is currently %s at %d strok\n", ret,l);
      l++;
    }
    commandSep[l]="\0";
    r=0;
    q=0;
    while (r < l)
    {
	ret = strtok(commandSep[r]," \n");
	printf("Found %s\n", ret);
	q = 0;
	while ( ret != NULL && q<16){
	  commands[r][q]= ret; 
	  ret = strtok(NULL," \n");
	printf("Found %s\n", ret);
	  q++;
	}
	commands[r][q] = NULL;
      r++;
      }

      debug(commands);
    
    if (strncmp(commands[0][0],"cd",2)==0){
      changedDir=cd(commands[0][1]);
        if (changedDir==0){
	printf("successful change\n");
      
	}
	else {
	  printf("change was not successful\n");
	}
      }   
//    else if (strncmp(commands[0][0],"pwd",3)==0){
//      pwd();
      //ret=strtok(NULL," ");  
//    }
    else{
      fork_and_exec(commands,l,STDIN_FILENO);
    }
  //debug(commands);
    
  }
  
  return 0;
}
/*
char * buf=NULL;
size_t length=0;
ssize_t line_length=getline(&buf,&length,stdin);

if(line_length==-1)
{return NULL;}
int delim_count=0;
for (char*tmp=buf; *tmp; tmp++) 
{
  delim_count+=*tmp=='(';
}

char *** all_commands=malloc(sizeof(char***[delim_count+2]));
for (i=0;i<delim_count+2; i++)
{
  all_commands[i]=NULL;
}
*/