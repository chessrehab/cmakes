#include <crypt.h>
#include "start01.h"
#include <pwd.h>
#include <grp.h>
#include <shadow.h>

#define _XOPEN_SOURCE
#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj03/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj03/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj03/data/test03.dat"
#define USRNAME "amanda"
#define USRID 1004
#define GRPNAME "vanessa"
#define GRPID 1003


int main() {
	struct passwd *passwd1,*passwd2;
	struct group *grp1,*grp2;
	struct spwd *spwd1,*spwd2;
	
	passwd1=getpwnam(USRNAME);
	passwd2=getpwuid(USRID);
	grp1=getgrnam(GRPNAME);
	grp2=getgrgid(GRPID);
	spwd1=getspnam(USRNAME);

	printf("\n%s user_name:%s\n",USRNAME,passwd1->pw_name);
	printf("%s user_uid:%d\n",USRNAME,passwd1->pw_uid);
	printf("%s user_grid:%d\n",USRNAME,passwd1->pw_gid);
	printf("%s user_desc:%s\n",USRNAME,passwd1->pw_gecos);
	printf("%s user_homedir:%s\n",USRNAME,passwd1->pw_dir);
	printf("%s user_shell:%s\n",USRNAME,passwd1->pw_shell);

	printf("\n%d user_name:%s\n",USRID,passwd2->pw_name);
	printf("%d user_uid:%d\n",USRID,passwd2->pw_uid);
	printf("%d user_grid:%d\n",USRID,passwd2->pw_gid);
	printf("%d user_desc:%s\n",USRID,passwd2->pw_gecos);
	printf("%d user_himedir:%s\n",USRID,passwd2->pw_dir);
	printf("%d user_shell:%s\n",USRID,passwd2->pw_shell);

	printf("\n%s group name:%s\n",GRPNAME,grp1->gr_name);
	printf("%s group pwd:%s\n",GRPNAME,grp1->gr_passwd);
	printf("%s group id:%ud\n",GRPNAME,grp1->gr_gid);
	printf("%s group members ptr:%p\n",GRPNAME,grp1->gr_mem);	

	printf("\n%d group name:%s\n",GRPID,grp2->gr_name);
	printf("%d group pwd:%s\n",GRPID,grp2->gr_passwd);
	printf("%d group id:%ud\n",GRPID,grp2->gr_gid);
	printf("%d group members ptr:%p\n",GRPID,grp2->gr_mem);	

	printf("\n%s shadow login name:%s\n",USRNAME,spwd1->sp_namp);
	printf("%s shadow enc pwd:%s\n",USRNAME,spwd1->sp_pwdp);
	printf("%s shadow time since last pwd change:%ld\n",USRNAME,spwd1->sp_lstchg);
	printf("%s shadow min days before pwd change:%ld\n",USRNAME,spwd1->sp_min);
	printf("%s shadow max nr of days before pwd change required:%ld\n",USRNAME,spwd1->sp_max);
	printf("%s shadow pwd change warning nr of days:%ld\n",USRNAME,spwd1->sp_warn);
	printf("%s shadow inactivation nr of days after expiration:%ld\n",USRNAME,spwd1->sp_inact);
	printf("%s shadow reserved for future use:%ld\n",USRNAME,spwd1->sp_expire);	
	    
	while((spwd2=getspent())!=NULL) {
		printf("\n%s shadow login name:%s\n",spwd2->sp_namp,spwd2->sp_namp);
		printf("%s shadow enc pwd:%s\n",spwd2->sp_namp,spwd2->sp_pwdp);
		printf("%s shadow time since last pwd change:%ld\n",spwd2->sp_namp,spwd2->sp_lstchg);
		printf("%s shadow min days before pwd change:%ld\n",spwd2->sp_namp,spwd2->sp_min);
		printf("%s shadow max nr of days before pwd change required:%ld\n",spwd2->sp_namp,spwd2->sp_max);
		printf("%s shadow pwd change warning nr of days:%ld\n",spwd2->sp_namp,spwd2->sp_warn);
		printf("%s shadow inactivation nr of days after expiration:%ld\n",spwd2->sp_namp,spwd2->sp_inact);
		printf("%s shadow reserved for future use:%ld\n",spwd2->sp_namp,spwd2->sp_expire);	
	}
	endspent();
	char heslo[20];
	printf("\n\nEnter password:");
	scanf("%s",heslo);
	printf("\nYou entered:%s\n",heslo);
	printf("\nI encrypted it as:%s\n",crypt(heslo,"xx"));

}




