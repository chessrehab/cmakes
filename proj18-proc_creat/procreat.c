#include "start01.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj18-proc_creat/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj18-proc_creat/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj18-proc_creat/data/test03.dat"

int main() {
	pid_t i;	
	int ex_status;
	switch(i=fork()) {
		case -1:
			errExit("forkin..");
		case 0:
			printf("child executing...");
			exit(18);
		default:
			printf("\nParent process spawned a child nr.:%d\n",i);	
			int y=wait(&ex_status);
			printf("\nchild nr %d exited with status %d\n",y,ex_status>>8);
	}

	    
}




