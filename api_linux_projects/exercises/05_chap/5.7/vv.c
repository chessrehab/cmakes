//this program implements readv and writev functions using only plain read and v


#include <fcntl.h>
// covers open
#include <unistd.h>
//covers read , write, close etc.
#include <sys/uio.h>
//covers iovec, writev, readv
#include <string.h>
//covers strcpy
#include <stdlib.h>
//covers malloc


ssize_t readv0(int,const struct iovec *, int);
ssize_t writev0(int,const struct iovec *,int);

int main(int argc, char *argv[]) {

	ssize_t bytes_read,bytes_written;
	int fd1,fd2,fd3;
	int id=0,id2=0;
	char note[20],note2[20];
	char fill='_';
	struct address {
		char first_name[20];
		char last_name[20];
		char street[40];
		int street_nr;
		char city[20];
		char zip[6];
	}adresa,adresa2;
	struct iovec iov[3];
	struct iovec iov2[3];
	

	memset(note,fill,sizeof(note));
	memset(note2,fill,sizeof(note2));
	memset(&adresa,fill,sizeof(adresa));
	memset(&adresa2,fill,sizeof(adresa2));
	//set the adresa data structure
	id=123;
	strcpy(note,"note");
	strcpy(adresa.first_name,"martin");
	strcpy(adresa.last_name,"svec");
	strcpy(adresa.street,"Racianska");
	adresa.street_nr=69;
	strcpy(adresa.city,"Bratislava");
	strcpy(adresa.zip,"831 02");


	iov[0].iov_base=&id;
	iov[0].iov_len=sizeof(id);
	iov[1].iov_base=note;
	iov[1].iov_len=sizeof(note);
	iov[2].iov_base=&adresa;
	iov[2].iov_len=sizeof(adresa);

	iov2[0].iov_base=&id2;
	iov2[0].iov_len=sizeof(id2);
	iov2[1].iov_base=note2;
	iov2[1].iov_len=sizeof(note2);
	iov2[2].iov_base=&adresa2;
	iov2[2].iov_len=sizeof(adresa2);

	


	fd1=open("test",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
	fd2=open("test",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	fd3=open("test2",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
	bytes_written=writev0(fd1,iov,3);
	lseek(fd1,0,SEEK_SET);
	bytes_read=readv0(fd2,iov2,3);
	bytes_written=writev0(fd3,&iov2[0],3);
	
	
	
	

	close(fd1);
	close(fd2);
	close(fd3);

}

ssize_t readv0(int fd, const struct iovec *iov, int iovcnt) {
	int buf_cnt=0,num_read;
	void *buf;
	for (int i=0;i<iovcnt;i++) {
		buf_cnt+=iov[i].iov_len;
	}
	buf=malloc(buf_cnt);
	num_read=read(fd,buf,buf_cnt);
	buf_cnt=0;
	for (int i=0;i<iovcnt;i++) {
		memcpy(iov[i].iov_base,buf+buf_cnt,iov[i].iov_len);
		buf_cnt+=iov[i].iov_len;
	}
	free(buf);
	return(num_read);
	
}

ssize_t writev0(int fd, const struct iovec *iov, int iovcnt) {
	int buf_cnt=0,num_written;
	void *buf;
	for (int i=0;i<iovcnt;i++) {
		buf_cnt+=iov[i].iov_len;
	}
	buf=malloc(buf_cnt);
	buf_cnt=0;
	for (int i=0;i<iovcnt;i++) {
		memcpy(buf+buf_cnt,iov[i].iov_base,iov[i].iov_len);
		buf_cnt+=iov[i].iov_len;
	}
	num_written=write(fd,buf,buf_cnt);
	
	free(buf);
	return(num_written);

}
