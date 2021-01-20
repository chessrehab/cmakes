#include <stdio.h>
#include <stdlib.h>

extern int mainASM(char,int,char*,int*);

int p=5;
int *pp=&p;
char c='m';
char *cp=&c;

int main(int argc, char *argv[]) {
	printf("Hello from c...\n");
	int rett=mainASM(c,p,cp,pp);
	printf("/n...back from c, return value:%d\n",rett);
	return(0);

}
