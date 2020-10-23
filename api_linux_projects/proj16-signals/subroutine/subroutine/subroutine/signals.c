//#define _GNU_SOURCE
#include "start01.h"
#include <signal.h>
#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj16-signals/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj16-signals/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj16-signals/data/test03.dat"
//#define _POSIX_C_SOURCE >=199309L

void handler1(int s) {
	printf("\nsignal recieved:%o\nsignal desc:%s\n",s,strsignal(s));
	psignal(s,"msg desc disgnal:");
}
static void handler_info(int sig,siginfo_t *siginfo,void *ucontext) {
	printf("\n signal recieved:%o(%s)\n",sig,strsignal(sig));
	printf ("\n signal info:si_signo:%d,si_code:%d\n",siginfo->si_signo,siginfo->si_code);
	printf ("\n \n");
}

int main() {
//	void (*fc_pointer)(int)=signal(2,handler1);
	sigset_t  pend_set,myset,myset2,fullmask,prevmask;

	if(sigemptyset(&myset)==-1) errExit("error:emptyset creation");
	if(sigaddset(&myset,SIGKILL)==-1) errExit("error:addset");
	if(sigaddset(&myset,SIGHUP)==-1) errExit("addset");
	if(sigaddset(&myset,SIGSTOP)==-1) errExit("addset");
	(sigismember(&myset,SIGKILL)==1) ? printf("\nkillsignal nr. 9 is member of signalset") : printf("\nkillsignal nr. 9 isnt a member of signalset");
	if(sigdelset(&myset,SIGKILL)==-1) errExit("delset");
	
	(sigismember(&myset,SIGKILL)==1) ? printf("\nkillsignal nr. 9 is member of signalset") : printf("\nkillsignal nr. 9 isnt a member of signalset");
	if(sigaddset(&myset,SIGKILL)==-1) errExit("addset");
	sigfillset(&fullmask);
	sigdelset(&fullmask,3);
//	sigdelset(&fullmask,59);
	sigprocmask(SIG_SETMASK,&fullmask,&prevmask);
	
	if(sigemptyset(&myset2)==-1) errExit("sigfillset");
	if(sigdelset(&myset2,SIGKILL)==-1) errExit("sigdelset");
	
	struct sigaction act;
	act.sa_sigaction=handler_info;
	sigfillset(&act.sa_mask);
	act.sa_flags= SA_SIGINFO ;
	
	for(int i=1;i<NSIG;i++) {
		sigaction(i,&act,NULL);	
//		printf("\nnumber:%d(%s)",i,strsignal(i));
	}
	
	
		
	sigpending(&pend_set);
	printf("\nPID:%d",getpid());
	printf("\nx");
    	sleep(15);
	sigpending(&pend_set);
	if(sigismember(&pend_set,59)) {
		printf("recieved signal 59!");
	} else { 
		printf("not");
	}
		
	
	//sigprocmask(SIG_SETMASK,&prevmask,NULL);
}




