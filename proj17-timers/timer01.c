#include "start01.h"
#include <sys/time.h>
#include <signal.h>
#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj17-timers/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj17-timers/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj17-timers/data/test03.dat"

void sig_handle(int s) {
	printf("\nSIGALRM:%d",SIGALRM);
	printf("\nsignal cought:%d",s);
}


int main() {
	for (int i=0;i<NSIG;i++) {
		signal(i,sig_handle);
	}
	struct timeval sekundy;
	struct itimerval timer;
	sekundy.tv_sec=1;
	sekundy.tv_usec=0;
	timer.it_value=sekundy;
	timer.it_interval=sekundy;
	raise(2);
	setitimer(ITIMER_REAL,&timer,NULL);
	while(1);
    
}




