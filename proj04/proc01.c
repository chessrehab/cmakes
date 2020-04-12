#include "start01.h"

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj03/data/test01.dat"
extern char **environ;

int main() {
	char *vall;
	//int pom=clearenv();
	if(putenv("MATO=somtu")!=0) errExit("error writing the env var");
	if(putenv("AMANDA=ajja")!=0) errExit("error writing the env var2");
	if(setenv("LONDO","frndo",1)!=0) errExit("error on setting env");
	if(unsetenv("AMANDA")!=0) errExit("error on unsetting");
	pid_t prid=getpid();
	pid_t parprid=getppid();
	printf("cislo tohto procesu je %ld\n",(long) prid);
	printf("cislo parent procesu je %ld\n",(long) parprid);
	char **ept=environ;
	int ctr=0;
	while(*ept!=NULL) {
		ctr++;
		printf("%d.premenna: %s\n",ctr,*(ept));
		ept++;
	}
	printf("\n\n\n");
	if(!(vall=getenv("MATO"))) errExit("Couldnt retrieve variable");
	printf("MATO variable value is:%s\n",vall);
//	while(1) {};
}


