 // program opens a file with O_APPEND flag , then seeks to the begining and writes data



#include <unistd.h>
//close,lseek,write  is in unistd.h
#include <string.h>
//strlen is in string.h
#include <fcntl.h>
//open is in fcntl.h

int main(int argc, char *argv[]) {

	int fop,num_read,num_wrote;
	off_t pos;
	char buf[]="hello...\0";


	fop=open("test",O_RDWR|O_APPEND|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
	num_wrote=write(fop,"pociatek.",10);	
	pos=lseek(fop,0,SEEK_SET);

	num_wrote=write(fop,buf,strlen(buf));
	
	close(fop);


}
