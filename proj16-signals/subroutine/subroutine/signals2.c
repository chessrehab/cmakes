

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

int main(int argc, char *argv[]) {

	printf("\nprogram:%s\natribut:%s",argv[0],argv[1]);



}




