#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//fatal error message
void fatal(char *message)  {
	char error_message[100];
	
	strcpy(error_message, "[!!] Fatal Error");
	strncat(error_message, message, 83);
	perror(error_message);
	exit(-1);
}
//dumping the data buffer from the packet to hex and to ascii chars
void dump(const unsigned char *data_buffer, const unsigned int length) {
	unsigned char byte;
	unsigned int i,j;
	for(i=0; i<length;i++) {
		byte=data_buffer[i];
		printf("%02x ",byte);
		if(((i%16)==15) || (i==length-1)) {
			for(j=0;j<15-(i%16);j++)
				printf("   ");
			printf("  |");
			for(j=(i-(i%16));j<=i;j++) {
				byte=data_buffer[j];
				if((byte>31) && (byte<127))
					printf("%c",byte);
				else
					printf(".");
			}
			printf("\n");
		}
	}
}
//sending strings to a socket with check on all bytes being sent
int send_string_tosocket(int fd_sock, unsigned char *buffer) {
	int sent_bytes, bytes_to_send;
	bytes_to_send=strlen(buffer);
	while (bytes_to_send>0) {
		sent_bytes=send(fd_sock,buffer,bytes_to_send,0);
		if(sent_bytes==-1) 
			return 0;
		bytes_to_send -=sent_bytes;
		buffer +=sent_bytes;
	}
	return 1;
}

//recieving strings from socket
int recv_line(int fd_sock, unsigned char *dest_buffer) {
#define EOL "\r\n"
#define EOL_SIZE 2
	unsigned char *ptr;
	int eol_matched=0;

	ptr=dest_buffer;
	while(recv(fd_sock,ptr,1,0)==1) {
		if(*ptr==EOL[eol_matched]) {
			 eol_matched++;
			if(eol_matched==EOL_SIZE) {
				*(ptr+1-EOL_SIZE)='\0';
				return strlen(dest_buffer);
			}
		} else {
			eol_matched=0;
		}
		ptr++;
	}
	return 0;
}

