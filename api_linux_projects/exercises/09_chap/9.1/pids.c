//check the result of process user ids



#define _GNU_SOURCE
#include <unistd.h>
//setuid,setreuid,seteuid,setfsuid,setresuid are covered in unistd.h
#include <stdio.h>
#include <stdlib.h>
//atoi is in stdlib.h
#include <sys/fsuid.h>
//fsuid is covered in sys/fsuid.h


int main (int argc, char * argv[]) {

	uid_t ruid,euid,suid,fsuid;

	getresuid(&ruid,&euid,&suid);
	fsuid=euid;

	printf("\n Starting: \t ruid:%d \t euid:%d \t suid:%d \t fsuid:%d \n",ruid,euid,suid,fsuid);
	
	if (atoi(argv[1])==1) {
	setuid(2000);
	getresuid(&ruid,&euid,&suid);
	fsuid=setfsuid(-1);
	printf("\n Question: What will PIDs look like after setuid(2000)?");
	printf("\n Answer: \t ruid:2000 \t euid:2000 \t suid:0 \t fsuid:2000 \n");
	printf("\n Reality: \t ruid:%d \t euid:%d \t suid:%d \t fsuid:%d \n",ruid,euid,suid,fsuid);
	}

	if (atoi(argv[1])==2) {
	setreuid(-1,2000);
	getresuid(&ruid,&euid,&suid);
	fsuid=setfsuid(-1);
	printf("\n Question: What will PIDs look like after setreuid(-1,2000)?");
	printf("\n Answer: \t ruid:1000 \t euid:2000 \t suid:0 \t fsuid:2000 \n");
	printf("\n Reality: \t ruid:%d \t euid:%d \t suid:%d \t fsuid:%d \n",ruid,euid,suid,fsuid);
	}

	if (atoi(argv[1])==3) {
	seteuid(2000);
	getresuid(&ruid,&euid,&suid);
	fsuid=setfsuid(-1);
	printf("\n Question: What will PIDs look like after seteuid(2000)?");
	printf("\n Answer: \t ruid:1000 \t euid:2000 \t suid:0 \t fsuid:2000 \n");
	printf("\n Reality: \t ruid:%d \t euid:%d \t suid:%d \t fsuid:%d \n",ruid,euid,suid,fsuid);
	}

	if (atoi(argv[1])==4) {
	setfsuid(2000);
	getresuid(&ruid,&euid,&suid);
	fsuid=setfsuid(-1);
	printf("\n Question: What will PIDs look like after setfsuid(2000)?");
	printf("\n Answer: \t ruid:1000 \t euid:0 \t suid:0 \t fsuid:2000 \n");
	printf("\n Reality: \t ruid:%d \t euid:%d \t suid:%d \t fsuid:%d \n",ruid,euid,suid,fsuid);
	}

	if (atoi(argv[1])==5) {
	setresuid(-1,2000,3000);
	getresuid(&ruid,&euid,&suid);
	fsuid=setfsuid(-1);
	printf("\n Question: What will PIDs look like after setresuid(-1,2000,3000)?");
	printf("\n Answer: \t ruid:1000 \t euid:2000 \t suid:3000 \t fsuid:2000 \n");
	printf("\n Reality: \t ruid:%d \t euid:%d \t suid:%d \t fsuid:%d \n",ruid,euid,suid,fsuid);
	}
		
}
