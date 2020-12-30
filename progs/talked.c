#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define BD_MAX_CLOSE 8192

int main(int argc, char *argv[]) {
	int maxfd, fd;	

//	printf("%s","hello!");
	switch(fork())  {		//first fork shuts down the parent process, making sure the process is a child of init
		case -1: return -1;	//error
		case 0: break;		//child process continues
		default: _exit(0);	//shutdown of parent process
	}
//	printf("%s","child!");
	if (setsid()==-1) 		//setting a new session id to break off the controlling terminal
		return -1;
	switch(fork()) {		//another fork makes sure that if the processs opens a terminal in the future it wont become controlling terminal
		case -1: return -1;	//error
		case 0: break;		//child continues
		default: _exit(0);	//parents shuts down
	}
	umask(0); 			//clear the umask of the process so it can open files with proper access right
	chdir("/");			//change the current working directory to root
	maxfd=sysconf(_SC_OPEN_MAX);	//getting to know max possible open filedescriptors
	if (maxfd=-1)
		maxfd= BD_MAX_CLOSE;
	for (fd=0; fd<maxfd; fd++) 	//shutting down all file descriptors
		close(fd);
	
	fd=open("/dev/null",O_RDWR);	//open 0 file descriptor to point to null input
	if (fd != STDIN_FILENO)		//make sure the fd equals 0
		return -1;
	if (dup2(STDIN_FILENO,STDOUT_FILENO)!=STDOUT_FILENO)	//duplicate standard output and standard error too
		return -1;
	if (dup2(STDIN_FILENO,STDERR_FILENO)!=STDERR_FILENO)
		return -1;
	


	pause();

}


