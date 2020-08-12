#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_auth( char *password) {
	char password_buffer[16];
	int auth_flag = 0;
	
	strcpy(password_buffer, password);
	
	if(strcmp(password_buffer,"amanda")==0) auth_flag=1;
	if(strcmp(password_buffer,"retaz")==0) auth_flag=1;

	return auth_flag;
}
int check_auth2(int password) {
	char password_buffer[16]="xxxxxxxxx\0";
	int auth_flag = 69;
	
	return auth_flag;
}

int main(int argc,char *argv[]) {
	unsigned int  a,b,c;
	char retaz[25]="zzzzzzzz\0";
	a=99;
	c=111;

	if(argc<2) {
		printf("Usage: %s <password> \n" ,argv[0]);
		exit(0);
	}
	if(check_auth2(a)) {
		printf ("woohooo");
	}	
	if(check_auth(argv[1])) {
		printf("-----Access GRANTED-----\n");
	} else {
		printf("!!!!! Access DENIED !!!!!\n");
		b=18;
	}
}
