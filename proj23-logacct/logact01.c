#define _GNU_SOURCE
#include "start01.h"
#include <utmpx.h>
#include <time.h>
#include <unistd.h>
#include <paths.h>

#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj23-logacct/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj23-logacct/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj23-logacct/data/test03.dat"

static char *type01(int nr) {
	switch(nr) {
		case 0:return "EMPTY";
		case 1:return "RUN_LVL";
		case 2:return "BOOT_TIME";
		case 3:return "NEW_TIME";
		case 4:return "OLD_TIME";
		case 5:return "INIT_PROCESS";
		case 6:return "LOGIN_PROCESS";
		case 7:return "USER_PROCESS";
		case 8:return "DEAD_PROCESS";
		default:return"unknown";
	}
}


int main() {
  setbuf(stdout,0);
  struct utmpx *ut;
  struct utmpx *wt;
  setutxent();
  printf("\nlogged in as:%s\n",getlogin());
  printf("\nreading the utmp file\n");
  while((ut=getutxent())!=NULL) {
	printf("\nut_type=%s\t",type01(ut->ut_type));
	printf("ut_pid=%d\t",ut->ut_pid);
	printf("ut_line=%-6.6s\t",ut->ut_line);
	printf("ut_id=%s\t",ut->ut_id);
	printf("ut_user=%s\t",ut->ut_user);
	printf("ut_host=%s\t",ut->ut_host);
	printf("ut_exit-e_termination=%d\t",ut->ut_exit.e_termination);
	printf("ut_exit-e_exit=%d\t",ut->ut_exit.e_exit);
	printf("ut_session=%d\t",ut->ut_session);
	time_t tv=(time_t)ut->ut_tv.tv_sec;
	printf("ut_tv-tv_sec=%s\t",ctime((time_t *) &tv)    );
	printf("ut_addr_v6=%d", ut->ut_addr_v6[0]);
	

  }
  printf("\nreading the wtmp file,located in %s\n",_PATH_WTMP);
  utmpxname(_PATH_WTMP);
  printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s","ut_type","ut_pid","ut_line","ut_id","ut_user","ut_host","ut_exit-terminat","ut_exit-exit","ut_session","ut_tv");
  while((wt=getutxent())!=NULL) {
	printf("\n%s\t",type01(wt->ut_type));
	printf("%d\t",wt->ut_pid);
	printf("%-6.6s\t",wt->ut_line);
	printf("%s\t",wt->ut_id);
	printf("%s\t",wt->ut_user);
	printf("%s\t",wt->ut_host);
	printf("%d\t",wt->ut_exit.e_termination);
	printf("%d\t",wt->ut_exit.e_exit);
	printf("%d\t",wt->ut_session);
	time_t tv=(time_t)wt->ut_tv.tv_sec;
	printf("%s\t",ctime((time_t *) &tv)    );
	printf("%d", wt->ut_addr_v6[0]);
  }

  	
  

}




