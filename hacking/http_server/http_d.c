#include "../lib/help_headers.h"

//#define WEBROOT "/home/martyx/webdocs/"
#define WEBROOT "./webdocs"

int get_file_size(int);

int main(int argc, char *argv[]) {
	int fd_sock,new_sock,fd_resource,length;
	unsigned char request[1024],resource[500];
	unsigned char *ptr;
	int yes=1,recv_length=0;
	struct sockaddr_in host_addr,client_addr;
	enum method {GET=1,HEAD=2};
	enum method mthd;
	socklen_t sock_addr_size=sizeof(struct sockaddr_in);

	//create a socket , bind it to a local port and start listening on it

	if ((fd_sock=socket(PF_INET,SOCK_STREAM,0))==-1) 
		fatal(" socket creation");

	if (setsockopt(fd_sock,SOL_SOCKET,SO_REUSEADDR, &yes,sizeof(int))==-1)
		fatal(" setting socket option");

	host_addr.sin_family=AF_INET;
	host_addr.sin_port=htons(6666);
	host_addr.sin_addr.s_addr=INADDR_ANY;
	memset(&(host_addr.sin_zero),'\0',8);
	if (bind(fd_sock,(struct sockaddr *) &host_addr,sizeof(struct sockaddr))==-1)
		fatal(" binding socket to the host");

	if(listen(fd_sock,20)==-1)
		fatal(" listening on socket");

	while(1) {
		printf("listening....\n");
		if((new_sock=accept(fd_sock, (struct sockaddr *) &client_addr, &sock_addr_size))==-1) 
			fatal(" accepting incoming connection ");
		printf("checkpoint\n");
		printf("Host %s, listening on port %d -Accepted a connection from:%s\tfrom port:%d\n",inet_ntoa(host_addr.sin_addr),ntohs(host_addr.sin_port),inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		recv_length=recv_line(new_sock, request);
		if (recv_length==0) 
			fatal(" recieving request");
		if ((ptr=strstr(request," HTTP/"))==NULL) {
			printf("%s","This is not a HTTP request..\n");
		} else {
			*ptr=0;
			ptr=NULL;
			if (strncmp(request,"GET ",4)==0)  {
				ptr=request+4;
				mthd=GET;
			}
			if (strncmp(request,"HEAD ",5)==0) {
				ptr=request+5;
				mthd=HEAD;
			}
		}
		if (ptr==NULL) {
			printf("%s","Unknown request \n");
		} else {
			if(ptr[strlen(ptr)-1]=='/') 
				strcat(ptr,"index.htm");
			strcpy(resource,WEBROOT);
			strcat(resource,ptr);
			fd_resource=open(resource,O_RDONLY,0);
			if(fd_resource==-1)
				printf("error:%d\n",errno);
			printf("Opening a resource:%s\n",resource);
			if(fd_resource==-1) {
				printf(" 404 Not Found\n");
				send_string_tosocket(new_sock, "HTTP/1.0 404 NOT FOUND\r\n");
				send_string_tosocket(new_sock, "Server: http_d \r\n\r\n");
				send_string_tosocket(new_sock, "<HTML><HEAD><TITLE>404 NOT FOUND</TITLE></HEAD> \r\n");
				send_string_tosocket(new_sock, "<BODY><H1>URL Not Found </H1></BODY></HTML> \r\n");
				
			} else {
				printf(" 200 OK\n");
				send_string_tosocket(new_sock, "HTTP/1.0 200 OK\r\n");
				send_string_tosocket(new_sock, "Server:http_d\r\n");
				if(mthd==GET) {
					if((length=get_file_size(fd_resource))==-1)
						fatal(" getting resource file");
					if((ptr=(unsigned char *) malloc(length))==NULL)
						fatal(" memory allocation");
					read(fd_resource,ptr,length);
					send(new_sock,ptr,length,0);
					free(ptr);
				}
				close(fd_resource);
			}
		}
		shutdown(new_sock,SHUT_RDWR);
	}
	return 0;
}
int get_file_size(int fd) {
	struct stat stat_struct;
	if(fstat(fd,&stat_struct)==-1)
		return -1;
	return (int) stat_struct.st_size;
}
	


