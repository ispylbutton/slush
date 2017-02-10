/*Spawn new processes with the fork() and execvp() system calls
Wait for child processes with the wait() system call
Perform complex input parsing in C
Pipe data between processes
Perform basic signal handling*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


#define LIMIT 512

void handler(int signal){
	if (signal == SIGINT){
				
	}	
}

bool error(char cmd[], int size){

	int i = 0;
	for (i; i < size-1; i++){

		// check for end of array
		if (cmd[i] == '\0') break;

		int j = i+1;
		char c = (char) cmd[j];

		// skip spaces
		while(c == ' ' && j < size){
		    c = cmd[++j];
		}
		
		if (cmd[i] == '(' && cmd[j] == '(') return true;
		if (cmd[i] == '(' && cmd[j] == '\n') return true;

		i = j-1;
	}

	return false;
}

int divide(char *source, char dest[][LIMIT], const char *delim){
	// Copy original string before tokenization
	char *original = malloc(strlen(source)+1);
	strcpy(original, source);
	
	
	char *chunk = strtok(source, delim);
        int count = 0;

        while (chunk != NULL){
                strcpy(dest[count++], chunk);
              	chunk = strtok(NULL, delim);
        }

	strcpy(source, original);
	
	return count;
}


int run_pipe(char cmd[][LIMIT], int index, int cmdCnt, int children, int fd[],  int fd_index){

	if (index < 0)  return children;

	char argv[LIMIT][LIMIT];
	const char delim = ' ';
	int size = divide(cmd[index], argv, &delim);
	
	char *cmds[size];
	int i = 0;
	for (i; i < size; i++) cmds[i] = argv[i];
	cmds[i] = NULL;

	// if cmd is chanage of directory
	if (strcmp(cmds[0], "cd") == 0){
		char dirs[2*size - 2];
        	i = 1;
	        int k, b = 0;

		// form path from tokenized command
        	for (i; i < size; i++){
			int len = strlen(argv[i]);
                	while(k < len){
                        	dirs[b++] = argv[i][k++];
	                }

                	if (i+1 != size) dirs[b++] = ' ';

	                 k = 0;
	        }

        	dirs[b] = '\0';

        	if (chdir(dirs) != 0){
                	perror("error");
	        }

	} else{

		// create pipe if not leftmost cmd
		if (index != 0){
			int tmp[2];
			if (pipe(tmp)){
				perror("error");
				exit(errno);
			}

			fd[fd_index] = tmp[0];
			fd[fd_index+1] = tmp[1];
	
		} 
	
	
		// fork and run
		switch(fork()){
			case 0:
				if (cmdCnt != 0){
					if (index == 0){ // leftmost cmd
						dup2(fd[fd_index-2], fileno(stdin)); 	// set the read end of previous pipe to stdin
						close(fd[fd_index-1]);			// close the write end of previous pipe
					}

					else if (index == cmdCnt){ // rightmost cmd
						dup2(fd[fd_index+1], fileno(stdout)); 	// set write end of pipe to the stdout
						close(fd[fd_index]);		   	// close the read end of current pipe
					}

					else{
						dup2(fd[fd_index-2], fileno(stdin)); 	// set read end of previous pipe to the stdin
						close(fd[fd_index-1]);			// close the write end of previous pipe

						dup2(fd[fd_index+1], fileno(stdout)); 	// set the write end of new pipe to the stdout
						close(fd[fd_index]);			// close the read end of current pipe
					}
				}
				if (execvp(argv[0], cmds) < 0){
					perror(argv[0]);
					exit(errno);
				}
			break;
	
			case -1:
				perror("error");
				exit(errno);
	
			default: // parent
				children++;
				if (cmdCnt != 0){
					if (index == 0){// leftmost cmd
	      					close(fd[fd_index-2]); // close the read end of the previous pipe
	   				 }
	
	   				 else if (index == cmdCnt){// rightmost cmd
						close(fd[fd_index+1]); 	// close the fd for the write end of pipe
						
	   				 }

					else {
						close(fd[fd_index+1]);
					}
				}
	
			
		}
	}

	index--;
	fd_index += 2;
	return run_pipe(cmd, index, cmdCnt, children, fd, fd_index);
} 

void run(char *cmd, int size, const char *delim){
	// Save tokens
	char argv[LIMIT][LIMIT];
	int tokenCount = divide(cmd, argv, delim);
	int fd[tokenCount*2];

	// check for number of commands
	if (tokenCount == 0){
		printf("Invalid command\n");
		return;
	}
			
	// run pipe recursively
	int children = run_pipe(argv, tokenCount-1, tokenCount-1, 0, fd, 0);

	// wait for children
	int status;
	while(children > 0){
		if (wait(&status) > 0) --children;
	}
}
 
int main(int argc, char *argv[]){

	char cmd[LIMIT];
	char dir[LIMIT];
	const char delim = '(';

	// Handle ctrl c
	if (signal(SIGINT, handler) == SIG_ERR){
		perror("error");
		exit(errno);
	}


	int size = strlen(getenv("HOME"));
	while(1){
		getcwd(dir, LIMIT);
		int sizedir = strlen(dir);
		int g = size;
		int i = 0;

		//print directory
		for (g; g < sizedir; g++){
			if (dir[g] == '/') dir[i++] = '|';
			else dir[i++] = dir[g];
		}
		dir[i] = '\0';
		
		printf("\nslush%s> ", dir);
		
		if (fgets(cmd, LIMIT, stdin) == NULL) break;

		// Check some errors
		if (error(cmd, LIMIT)) printf("Invalid null\n");

		// Run command		
		else{
			char *p = strchr(cmd, '\n');
			if (p != NULL) *p = '\0';

			 run(cmd, LIMIT, &delim);
		}
	}

	//perror("error");

	return 0;

}