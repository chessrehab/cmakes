#define _DEFAULT_SOURCE
#include "start01.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>


#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj18-proc_creat/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj18-proc_creat/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj18-proc_creat/data/test03.dat"

static void before_exit() {
	printf("\nexiting in function registered by ataxit...\n");
}
static void before_on_exit(int ex_status, void *arg) {
	printf("\n exiting in function registered by on_exit...exit status code:%d\n with an argument:%d\n",ex_status,*((int *)arg));
}
static void sig_handler(int s) {
	int stat;
	if(s==SIGCHLD) {
		int pid=waitpid(-1,&stat,WUNTRACED|WCONTINUED);
		if(pid>0) {
			
			
			printf("\nsignal caught:%d\n",s);		
			printf("\nsignal status:%o\n",stat);
	
			if(WIFEXITED(stat)) printf("\nnormal exit with exit_status:%d\n",stat>>8);
//			if(WIFSIGNALED(stat)==1) printf("\nkilled with:%d \ncore dumped:%d\n",WTERMSIG(stat),WCOREDUMP(stat));
			if(WIFSIGNALED(stat)==1) printf("\nkilled with:%d\ncore dumped:%d\n",stat & 127,(stat & 255)>>7);
			if(WIFSTOPPED(stat)) {
				printf("\nstopped\n");
			}
			if(WIFCONTINUED(stat)) printf("\ncontinued..\n");
		}

	}		
	fflush(stdout);	
}

int main() {
	struct sigaction sa;
	sigset_t blockmask,emptymask;
	sa.sa_flags=0;
	sa.sa_handler=sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGCHLD,&sa,NULL);
	pid_t i=0;	
	int ex_status=0;
	atexit(before_exit);
	on_exit(before_on_exit,(void *) &i);
	switch(i=fork()) {
		case -1:
			errExit("forkin..");
		case 0:
			printf("child executing...");
			sleep(5);
			raise(15);
			//sleep(5);
			sleep(5);
			exit(18);
		default:
			printf("\nParent process spawned a child nr.:%d\n",i);	
			//int y=wait(&ex_status);
			//printf("\nchild nr %d  exited with status %d\n",y,ex_status>>8);
			while(1);
	}

	    
}




