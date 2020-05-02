

//#define _GNU_SOURCE
#include "start01.h"
#include <signal.h>
#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj16-signals/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj16-signals/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj16-signals/data/test03.dat"
//#define _POSIX_C_SOURCE >=199309L



int main(int argc, char *argv[]) {
	union sigval xx;
	xx.sival_int =69;
	printf("\nprogram:%s\natribut:%s",argv[0],argv[1]);
	sigqueue(atoi(argv[1]),59,xx);	
	for(int i=0;i<10;i++) {
		
		
		sigqueue(atoi(argv[1]),61,xx);
		sleep(3);
	}



}




