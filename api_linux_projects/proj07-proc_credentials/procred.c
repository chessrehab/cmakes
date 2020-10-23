#include "start01.h"

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj07-proccred/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj07-proccred/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj07-proccred/data/test03.dat"

void vypis_ids(char *);
int main(int argc, char *argv[]) {
	vypis_ids("start");	
	if(setuid(atoi(argv[1]))==-1) errExit("couldnt set an id");
	vypis_ids("after changing ids to 0");
	    
}
void vypis_ids(char *msg) {
	uid_t real_uid,eff_uid,set_uid;
	gid_t real_gid,eff_gid,set_gid;

	
	printf(".........................%s.......................................\n",msg);

	real_uid=getuid();
	printf("\nreal uid of this process is: %d\n",real_uid);
    
	real_gid=getgid();
	printf("real_gid of this process is: %d\n",real_gid);
	
	eff_uid=geteuid();
	printf("effective uid of this process is: %d\n",eff_uid);
	
	eff_gid=getegid();
	printf("effective group id of this  process is: %d\n",eff_gid);
	
}




