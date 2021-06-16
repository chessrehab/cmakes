
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "help_funct_head.h"

int main(void) {

	int i,recv_length,sock_fd;
	unsigned char buffer[9000];

	if ((sock_fd=socket(PF_INET, SOCK_RAW, IPPROTO_TCP))==-1)
		fatal("socket creation");

	while(1) {
		recv_length=recv(sock_fd,buffer,8000,0);
		printf("Got a %d byte packet\n", recv_length);
		dump(buffer,recv_length);
	};
};
