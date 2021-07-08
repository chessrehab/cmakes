//implement system call getpwnam() using setpwent(), getpwent() and endpwent()







#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
//getpwent covered in pwd.h and sys/types.h
#include <string.h>


//prototypes
extern struct passwd *getpwent(void);
extern void setpwent(void);
extern void endpwent(void);
struct passwd *pwd;

struct passwd *getpwnam0(const char *name) {

	setpwent();


	for (pwd=getpwent();pwd!=NULL;) {
		if (strcmp(pwd->pw_name,name)==0) return pwd;
		pwd=getpwent();
	}

	endpwent();
	return NULL; 

}
int main(int argc,char *argv[]) {

	struct passwd *pwd_main;
	pwd_main=getpwnam0("root");
	printf("\n root uid is:%d\n",pwd_main->pw_uid);
	pwd_main=getpwnam0("mx");
	printf("\n root uid is:%d\n",pwd_main->pw_uid);
	
	return 0;



}


