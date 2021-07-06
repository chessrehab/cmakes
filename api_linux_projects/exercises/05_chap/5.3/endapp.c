//the program will write a lot of bytes to file that is eaither opened with append flag or without it.
//it will test the difference between atomic approach of append flg and non_atomic approach of seek-to-end write by running two instances \
// of the program simultaneously
//usage: endapp fileno num_bytes app_method    {x serves as an identifier if append should be used or not}



#include <fcntl.h>
//open need fcntl.h
#include <unistd.h>
//close, lseek , write need unistd.h
#include <stdlib.h>
//atol is in stdlib.h
#include <string.h>
//strcmp need string.h

int main(int argc, char *argv[]) {

	int fd,num_wrote;
	int a=0;	
	char x[]="x";	

	if (strcmp(argv[3],"a\0")==0) a=1;
	fd=open(argv[1],a ? O_RDWR|O_CREAT|O_APPEND : O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);


	for (int i=0;i<atol(argv[2]);i++) {
		if (a) lseek(fd,0,SEEK_END);
		num_wrote=write(fd,x,1);
	}

	close(fd);
}
