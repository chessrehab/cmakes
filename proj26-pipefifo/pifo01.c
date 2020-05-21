#include "start01.h"
#include <unistd.h>
#include <sys/wait.h>

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj26-pipefifo/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj26-pipefifo/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj26-pipefifo/data/test03.dat"

int main() {
    
	int pfd[2];
	if(pipe(pfd)==-1)
		errExit("pipe creation..");
	switch(fork()) {
		case -1: errExit("forking error");
		case 0:
			close(pfd[0]);
			dup2(pfd[1],1);
			close(pfd[1]);
			execlp("ls","ls","-al",(char *) NULL);
			
		default:
			break;
	}
	printf("parent: fork1 done...\n");
	switch(fork()) {
		case -1:errExit("fork2");
		case 0:
			close(pfd[1]);
			dup2(pfd[0],0);
			close(pfd[0]);
			execlp("wc","wc",(char *) NULL);
		default:
			break;
	}
	printf("parent: fork2 done...\n");
	close(pfd[0]);
	close(pfd[1]);
  	wait(NULL);
	wait(NULL);
	printf("parent: forked child joined, exiting...\n");
	return(0);
	
	
	
}

/*
int main() {
    
	int pfd[2];
	if(pipe(pfd)==-1)
		errExit("pipe creation..");
	switch(fork()) {
		case -1: errExit("forking error");
		case 0:
			close(pfd[0]);
			printf("child:writing to pipe...\n");
			write(pfd[1],"hello parent\0",13);
			exit(0);
		default:
			close(pfd[1]);
			char buf[13];
			read(pfd[0],&buf,13);
			printf("parent: read from pipe:%s\n",buf);
		        wait(NULL);
			printf("parent: forked child joined, exiting...\n");
			return(0);
	}
}

*/


