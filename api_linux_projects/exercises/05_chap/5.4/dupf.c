//program implements duplication file descriptors using fcntl system calls



#include <fcntl.h>
//fcntl,open needs fcntl.h
#include <unistd.h>
//write,close needs unistd.h
#include <stdio.h>
//printf need stdio.h


int dupfx(int);
int dupfx2(int,int);

int main(int argc,char *argv[]) {



	int fd,fd_new1,fd_new2,fd_help;

	fd=open("test",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
	
//	fd_new1=dup2(fd,3);
//	fd_new2=dup2(STDOUT_FILENO,4);

//	fd_new1=dupfx(fd);
//	fd_new2=dupfx(fd);

	fd_help=dup2(STDOUT_FILENO,16);

	fd_new1=dupfx2(fd,13);
	fd_new2=dupfx2(fd,16);

	
	printf("\nfd_new1=%d\nfd_new2=%d\n",fd_new1,fd_new2);

	write(fd_new2,"\nfrom fd_new2\n",14);

	close(fd);
	close(fd_new1);
	close(fd_new2);

}

int dupfx(int fd) {

	return fcntl(fd,F_DUPFD,0);

}

int dupfx2(int fd,int fd_new) {

	int i;
	i=fcntl(fd_new,F_GETFD);
	if (i!=-1) close(fd_new);
	return fcntl(fd,F_DUPFD,fd_new);

}
