#include "start01.h"

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj03/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj03/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj03/data/test03.dat"

int main() {
	int *ip;
	printf("program break is at: %p\n",sbrk(0));
	void *pt=malloc(10*sizeof(char));
	printf("program break is at: %p\n",sbrk(0));	
	free(pt);
	printf("program break is at: %p\n",sbrk(0));	
	void *pt2=calloc(10000000000,10*sizeof(int));
	printf("program break is at: %p\n",sbrk(0));	
	void *pt3=realloc(pt2,100);
	printf("program break is at: %p\n",sbrk(0));	
        free (pt3);
	free (pt2);
	int *pt4=calloc(11,sizeof(int));
	for(int i=0;i<10;i++) {
		pt4[i]=i+1;
	};
        pt4[10]=NULL;
	
	for(ip=pt4;(*ip)!=NULL;ip++)  {
                printf("adresa:%p",ip);
		printf("cislo:%d\n",*ip);
	}
	free(pt4);	
	
	
	
}
