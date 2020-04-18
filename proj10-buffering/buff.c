#include "start01.h"

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj10-buffering/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj10-buffering/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj10-buffering/data/test03.dat"
static char buf[MAX_BUF];

int main() {

	FILE *stream1=fopen(PATH01,"rw");
	if(setvbuf(stream1,buf,_IONBF,MAX_BUF)!=0) errExit("buffer error");
	setbuf(stream1,buf);
	printf("\nfile descriptor:%d\n",fileno(stream1));
	FILE *stream2=fdopen(fileno(stream1),"a");
	fclose(stream1);
	char x[]="h";
	
	size_t ii=fwrite(x,sizeof(char),1,stream2);
		    
	fclose(stream2);

}




