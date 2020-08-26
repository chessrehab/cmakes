#include "../lib/help_headers.h"
#include <netdb.h>

int main(int argc, char * argv[]) {
	struct hostent *host_info;
	struct in_addr *address,*address2;
	struct sockaddr_in target_addr;
	int fd_sock;
	char buffer[1024];

	if (argc<2) {
		printf("Usage is: %s <hostname> \n", argv[0]);
		exit(1);
	}

	host_info= gethostbyname(argv[1]);
	if(host_info==NULL) {
		printf("Couldn't lookup %s \n",argv[1]);
	} else {
		address=(struct in_addr *) (host_info->h_addr);
		printf("%s has address %s \n", argv[1],inet_ntoa(*address));
	}

	char *alias;
	int ctr;

	ctr=0;
	while (alias=host_info->h_aliases[ctr]) {
		printf("Alias %d:%s \n",ctr, alias);
		ctr++;
	}
	char *nm;
	ctr=0;
	while (nm=host_info->h_addr_list[ctr]) {
		address2=(struct in_addr*) nm;
		printf("Addr list %d:%s \n",ctr,inet_ntoa(*address2));
		ctr++;
	}

	if((fd_sock=socket(PF_INET,SOCK_STREAM,0))==-1) 
		fatal(" socket creation");

	
	target_addr.sin_family=AF_INET;
	target_addr.sin_port=htons(80);
	target_addr.sin_addr= *address;
	memset(&(target_addr.sin_zero),'\0',8);
	
	if (connect(fd_sock,(struct sockaddr*) &target_addr,sizeof(struct sockaddr))==-1) 
		fatal(" connect");
	
	send_string_tosocket(fd_sock,"HEAD / HTTP/1.1\r\n\r\n");
	ctr=0;
	while (recv_line(fd_sock,buffer)) {
		//if(strncasecmp(buffer,"Server:",7)==0) {
			printf("Line %d: %s \n",ctr, buffer);
			ctr++;
		//exit(0);
		//}
	}
	//printf("%s","Server not found..\n");
	//exit(1);
	
	
}



