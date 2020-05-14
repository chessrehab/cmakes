#include <stdlib.h>
#include <syslog.h>
#include "start01.h"
#include <unistd.h>
#include <stdio.h>
#include "become_daemon.h"
#include <signal.h>

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj22-daemons/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj22-daemons/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj22-daemons/data/test03.dat"


static void hu_handler(int sig) {
	syslog(LOG_EMERG,"%s","hangup handler activated");
}

int main(int argc,char *argv[]) {
	
	printf("\npid:%lld",(long long) getpid());
	printf("\nppid:%lld",(long long) getppid());
	printf("\npgid:%lld",(long long) getpgrp());
	printf("\nsid:%lld",(long long) getsid(0));
	printf("\nTTY:%s\n",ctermid(NULL));
	setbuf(stdout,NULL);
	int resp= becomeDaemon(0);
//	printf("\nlaunching daemon:%d",resp);	
	

// daemon initiaties from here
	struct sigaction sa;
	char *pwd;
	pwd=getenv("PWD");
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=SA_RESTART;
	sa.sa_handler=hu_handler;
	sigaction(SIGHUP,&sa,NULL);
	openlog(argv[0],0,LOG_USER);	
	int i;
	for(;;) {
		sleep(5);
		syslog(LOG_WARNING,"%s%d","sleeping...",i);
		syslog(LOG_INFO,"%s",pwd);
		system("echo xyz > my_log.log");
		i++;
	
	}	
	closelog();
	
	
	
}




