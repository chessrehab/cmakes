#include "start01.h"
#include <sys/xattr.h>
#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj13-ext_fileattr/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj13-ext_fileattr/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj13-ext_fileattr/data/test03.dat"

int main() {
	int fd1=open(PATH01,O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IXUSR);
	void *val1=malloc(10*sizeof(char));
	//memset(val1,'x',10);
	size_t size1=10;
	ssize_t xtt1=fgetxattr(fd1,"user.xxxx",val1,size1);
	printf("\nuser.x=%s\n",val1);
	void *val2="hodnota2\0";   
	int xtt2=fsetxattr(fd1,"user.xxxx",val2,size1,0);
	void *val3=malloc(10*sizeof(char));
	ssize_t xtt3=fgetxattr(fd1,"user.xxxx",val3,size1);
	printf("\nuser.x=%s\n",val3);   
	void *val4="hod4\0";
	int xtt4=fsetxattr(fd1,"user.y",val4,size1,0);
	char *list1=malloc(30*sizeof(char));
	ssize_t xtt5= flistxattr(fd1,list1,30);
	printf("%d",xtt5);
	for(int ls=0;ls<xtt5;ls+=strlen(&list1[ls])+1) printf("\nlist%d=%s\n",ls,&list1[ls]);
	   
	


	
}




