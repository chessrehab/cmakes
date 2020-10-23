#define _GNU_SOURCE
#include "start01.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdio.h>

#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj19-exec/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj19-exec/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj19-exec/data/test03.dat"

void ex1() {
	printf("exiting parent...");

}
int  clonned(void *vd) {
	printf("\nentered the clonned func");
	printf("\n message from other galaxy:%s\n",(char *) vd);
	exit(0);
}


int main(int argc, char *argv[]) {
	atexit(ex1);
	int fk,stat,stat2;
	switch (fk=fork()) {
		case -1:
			errExit("forky error...");
		case 0:
			execv("../proj14-dirs/dirs",argv);
			_exit(0);
		
		default:
			waitpid(fk,&stat,0);
			printf("\nchild did its job and exited with a code:%d\n",stat);
			system("ps -al| grep exec01");
//			system("gitsync");
			void *stck=malloc(64000);
			void *stck_top=stck+64000;
			char msg[]="ahojte";
			pid_t new_cloned_pid= clone(clonned,stck_top,CLONE_VM|CLONE_SIGHAND|SIGUSR1,&msg);
			pid_t i=waitpid(new_cloned_pid,&stat2,__WCLONE);
			printf("\n%d\n",i);
			printf("\n%d joined!\n",i);
			fflush(stdout);
			exit(0);
	}
}




