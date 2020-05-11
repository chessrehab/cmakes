#include <unistd.h>
#include "start01.h"

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj21-procgroups/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj21-procgroups/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj21-procgroups/data/test03.dat"


int main() {
	setbuf(stdout,NULL);
	printf("\nproc id:%d\n",getpid());
	printf("\nproc group id:%d\n", getpgrp());	
	switch(fork()) {
		case -1:
			errExit("fork");
		case 0:
			printf("\nchild proc id:%d",getpid());
			printf("\nchild proc group id:%d\n", getpgrp());	
			setpgid(0,0);
			printf("\n2 child proc id:%d",getpid());
			printf("\n2 child proc group id:%d\n", getpgrp());	
			exit(0);

		default:
			printf("\nparent proc id:%d",getpid());
			printf("\nparent proc group id:%d\n", getpgrp());	
	}
}




