#include "../lib/help_headers.h"


int main(void) {
	printf("%s","startin a tcp/ip server on port 6666...\n");
	//initialization of variables and structures
	int fd_sock,fd_conn_sock;
	struct sockaddr_in host_addr,client_addr;
	socklen_t sin_size;
	int recv_length=1, yes=1;
	char buffer[1024];

	//1. socket creation
	if((fd_sock=socket(PF_INET,SOCK_STREAM,0))==-1) 
		fatal("in socket");
	

	//2. setting socket option to reuse address on port if busy
	if((setsockopt(fd_sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)))==-1)
		fatal("setting socket option");

	//initialization of host(server) address structure
	host_addr.sin_family=AF_INET;
	host_addr.sin_port=htons(PORT);
	host_addr.sin_addr.s_addr=0; //my own localhost ip addrress
	memset(&(host_addr.sin_zero),'\0',8); //nullification of padding area in address structure

	//3. binding the socket to the host(server address
	if(bind(fd_sock,(struct sockaddr*) &host_addr,sizeof(struct sockaddr))==-1) 
		fatal("binding socket to a host address");
	
	//4. setting the socket to listen on a host address
	if(listen(fd_sock, 5)==-1)
		fatal("listening on local host(server) address");

	//loop that will accept requests
	while(1) {
		sin_size=sizeof(struct sockaddr_in);
		if((fd_conn_sock=accept(fd_sock, (struct sockaddr*) &client_addr, &sin_size))==-1) // accepting connection and making a socket for it
			fatal("accepting connection");	
		printf("server info: got connected to: %s, on port: %d, socket: %d \n", inet_ntoa(client_addr.sin_addr),client_addr.sin_port, fd_conn_sock);
		send(fd_conn_sock, "Connected to server...\n",23,0);
		recv_length= recv(fd_conn_sock,&buffer,1024,0);
		while (recv_length>0) {
			printf("Message from %s, on port %d, on socket %d, with length:%d, msg: \n", inet_ntoa(client_addr.sin_addr),client_addr.sin_port, fd_conn_sock,recv_length);
			dump(buffer, recv_length);
			recv_length=recv(fd_conn_sock,&buffer,1024,0);
		}
	printf("Closing the connection to: %s, on port: %d, socket: %d \n", inet_ntoa(client_addr.sin_addr),client_addr.sin_port,fd_conn_sock);
	shutdown(fd_conn_sock,2);
	}
	printf("Shutting down the server: %s, on port: %d, socket: %d \n", inet_ntoa(host_addr.sin_addr),host_addr.sin_port,fd_sock);
	return 0;

}


