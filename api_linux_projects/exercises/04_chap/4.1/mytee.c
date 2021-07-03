// tee program reads from standard input and outputs the text to standard output \
// as well as to the file that is specified in the commandline attribute
// by default mytee overwrites any existing file with specified name
// command line option -a causes the program to append to existing file
// usage: mytee [OPTION]... [FILE]...
// options: -a  {appends to given FILE(s)}



#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
//malloc and abort is part of stdlib.h
//printf is part of stdio.h 
//open() is part of fnctl.h
//getopt() is part of unistd.h

#define MAXREAD 100

int main(int argc, char *argv[]) {
	int c,i,char_read,char_written;
	int app=0;
	int files_cnt=0;
	int *fd_arr;
	char buf[100];
	
	

	while ((c=getopt(argc,argv,"a"))!=-1) {
		switch (c) {
			case 'a':
				app=1;
				break;
			case '?':
				printf("wrong argument:%c",optopt);
				abort();
				break;
			default:
				break;
		}
	}
	
	files_cnt=argc-optind;

	if (files_cnt) {
		fd_arr=malloc(files_cnt * sizeof(int));
		for (i=0; i<files_cnt; i++) {
			fd_arr[i]=open(argv[optind+i],(app==1) ? O_RDWR|O_CREAT|O_APPEND : O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);

		}
	}

	while (char_read=read(STDIN_FILENO,buf,MAXREAD)) {

		char_written=write(STDOUT_FILENO,buf,char_read);
		if (files_cnt) {
			for (i=0;i<files_cnt;i++) {
				char_written=write(fd_arr[i],buf,char_read);
			}
		}
	}
	
	if (files_cnt) {
		for (i=0;i<files_cnt;i++) {
			close(fd_arr[i]);
		}
		free(fd_arr);
	}

}

