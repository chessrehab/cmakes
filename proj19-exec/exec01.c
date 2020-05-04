#include "start01.h"
#include <unistd.h>
#include <sys/wait.h>

#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj19-exec/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj19-exec/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj19-exec/data/test03.dat"

int main(int argc, char *argv[]) {
	int fk,stat;
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
			system("gitsync");
			exit(0);
	}
}




