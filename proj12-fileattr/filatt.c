#include "start01.h"
#include <sys/stat.h>

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj12-fileattr/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj12-fileattr/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj12-fileattr/data/test03.dat"
#define UMSK (S_IWUSR|S_IWGRP|S_IWOTH|S_IXOTH|S_IROTH)


int print_stat(int fd1,struct stat *stb) {
	if(fstat(fd1,stb)==-1) errExit("getting file attrs");
	printf("\nst_dev:%d\n",stb->st_dev);
	printf("st_ino:%d\n",stb->st_ino);
	printf("st_mode:%o\n",stb->st_mode);
	printf("st_nlink:%d\n",stb->st_nlink);
	printf("st_uid:%d\n",stb->st_uid);
	printf("st_gid:%d\n",stb->st_gid);
	printf("st_rdev:%d\n",stb->st_rdev);
	printf("st_size:%d\n",stb->st_size);
	printf("st_blksize:%d\n",stb->st_blksize);
	printf("st_blocks:%d\n",stb->st_blocks);
	printf("st_atime:%d\n",stb->st_atime);
	printf("st_mtime:%d\n",stb->st_mtime);
	printf("st_ctime:%d\n",stb->st_ctime);
	return 0;
}

int main() {
	struct stat *stb=malloc(sizeof(struct stat));
	int fd1=open(PATH01,O_RDWR | O_CREAT,S_IRUSR,S_IWUSR,S_IXUSR,S_IRGRP,S_IXGRP,S_IROTH);
	mode_t mt=umask(UMSK);
	printf("\nset the u mask to:%o\n",mt);
	mt=umask(UMSK);
	printf("\nnow set the u mask to:%o\n",mt);
	print_stat(fd1,stb);
	int fd2=open(PATH02,(O_RDWR|O_CREAT|O_TRUNC));
	print_stat(fd2,stb);
}




