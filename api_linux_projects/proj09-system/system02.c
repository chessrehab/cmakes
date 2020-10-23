#include "start01.h"
#include <sys/utsname.h>
#define MAX_BUF 100
#define _UTSMAX 65
#define PATH01 "/home/marty/cmakes/proj09-system/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj09-system/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj09-system/data/test03.dat"

int main() {
	printf("\n _SC_ARG_MAX:%li\n",sysconf(_SC_ARG_MAX));
	printf(" _SC_CLK_TCK:%li\n",sysconf(_SC_CLK_TCK));
	printf(" _SC_LOGIN_NAME_MAX:%li\n",sysconf(_SC_LOGIN_NAME_MAX));
	printf(" _SC_OPEN_MAX:%li\n",sysconf(_SC_OPEN_MAX));
	printf(" _SC_NGROUPS_MAX:%li\n",sysconf(_SC_NGROUPS_MAX));
	printf(" _SC_PAGE_SIZE:%li\n",sysconf(_SC_PAGE_SIZE));
	printf(" _SC_RTSIG_MAX:%li\n",sysconf(_SC_RTSIG_MAX));
	printf(" _SC_SIGQUEUE_MAX:%li\n",sysconf(_SC_SIGQUEUE_MAX));
	printf(" _SC_STREAM_MAX:%li\n",sysconf(_SC_STREAM_MAX));
	
	printf("\n _PC_NAME_MAX:%li\n",pathconf("/",_PC_NAME_MAX));
	printf(" _PC_PATH_MAX:%li\n",pathconf("/",_PC_PATH_MAX));
	printf(" _PC_PIPE_BUF:%li\n",pathconf("/",_PC_PIPE_BUF));

	struct utsname uts1;
	if (uname(&uts1)==-1) errExit("uts structure error");
	printf("\n sysname:%s\n",uts1.sysname);
	printf("nodename:%s\n",uts1.nodename);
	printf("release:%s\n",uts1.release);
	printf("version:%s\n",uts1.version);
	printf("machine:%s\n",uts1.machine);
	printf("domainname:%s\n",uts1.__domainname);

	
}




