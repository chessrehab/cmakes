// program that copies file with holes to a new file with corresponding holes
//usage  cphole [FILE_source] [File_dest]



#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//fcntl.h includes open()
//string.h includes strlen()

#define MAX_READ 1024


int main(int argc, char *argv[]) {

	int fd1,fd2,fd_new,nr_read,nr_wrote;
	off_t seeked;
	char buf[MAX_READ];
	char buf0[]="hello hello starting...\0";

	
	fd_new=open("new_file_with_holes",O_RDWR|O_CREAT|O_TRUNC|O_SYNC,S_IRUSR|S_IWUSR);
	nr_wrote=write(fd_new,buf0,strlen(buf0));
	seeked=lseek(fd_new,100000,SEEK_END);
	nr_wrote=write(fd_new,buf0,strlen(buf0));
	close(fd_new);

	fd1=open("new_file_with_holes",O_RDONLY);
	fd2=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);

	while(nr_read=read(fd1,buf,MAX_READ)) {
		nr_wrote=write(fd2,buf,nr_read);
	}

	close(fd1);
	close(fd2);

}





