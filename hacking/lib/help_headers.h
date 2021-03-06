#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define PORT 6666

//fatal error message
void fatal(char *); 
//dumping the data buffer from the packet to hex and to ascii chars
void dump(const unsigned char *, const unsigned int); 
//sending strings to socket
int send_string_tosocket(int,unsigned char *);
//recieving strings from socket
int recv_line(int,unsigned char *);

