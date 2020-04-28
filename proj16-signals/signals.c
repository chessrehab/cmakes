
#include "start01.h"
#include <signal.h>
#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj16-signals/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj16-signals/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj16-signals/data/test03.dat"
//_POSIX_C_SOURCE >=1 || _XOPEN_SOURCE || _POSIX_SOURCE
void handler1(int s) {
	printf("\nsignal recieved:%o\nsignal desc:%s\n",s,strsignal(s));
	psignal(s,"msg desc disgnal:");
}

int main() {
	void (*fc_pointer)(int)=signal(2,handler1);
	sigset_t  myset;
	if(sigemptyset(&myset)==-1) errExit("error:emptyset creation");
	if(sigaddset(&myset,SIGKILL)==-1) errExit("error:addset");
	if(sigaddset(&myset,SIGHUP)==-1) errExit("addset");
	if(sigaddset(&myset,SIGSTOP)==-1) errExit("addset");
	(sigismember(&myset,SIGKILL)==1) ? printf("\nkillsignal nr. 9 is member of signalset") : printf("\nkillsignal nr. 9 isnt a member of signalset");
	if(sigdelset(&myset,SIGKILL)==-1) errExit("delset");
	
	(sigismember(&myset,SIGKILL)==1) ? printf("\nkillsignal nr. 9 is member of signalset") : printf("\nkillsignal nr. 9 isnt a member of signalset");
	
	if(sigprocmask(SIG_SETMASK,&myset,NULL)==-1) errExit("sigprocmask");
	
    	while(1);

}




