#include <pcap.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "help_funct_head.h"

struct ether_hdr ether_hdr0;
struct ip_hdr ip_hdr0;
struct tcp_hdr tcp_hdr0;
	

void pcap_fatal(const char *failed_in, const char *errbuf) {
	printf("Fatal error in %s: %s\n", failed_in,errbuf);
	exit(1);
}

void callback_packet_caught(u_char *,const struct pcap_pkthdr *, const u_char *);

//typedef void (*pcap_handler)(u_char *, const struct pcap_pkthdr *, const u_char *);

void decode_ethernet(const u_char *);
void decode_ip(const u_char*);
int decode_tcp(const u_char*);
void print_packet(u_char *,int,int);

int main(void) {

	struct pcap_pkthdr p_header;
	const u_char *packet,*packet_data;
	char errbuf[PCAP_ERRBUF_SIZE];
	char *device;
	pcap_t *pcap_handle;
	
	device=pcap_lookupdev(errbuf);
	if(device == NULL)
		pcap_fatal("pcap_lookupdev",errbuf);
	printf ("Sniffing on device %s \n",device);
	pcap_handle = pcap_open_live(device,4096,1,0,errbuf);
	if(pcap_handle==NULL)
		pcap_fatal("pcap_open_live",errbuf);
	//while(1) {
	//	packet=pcap_next(pcap_handle, &p_header);
	//	printf("Got a %d byte packet \n",p_header.len);
	//	dump(packet,p_header.len);
	//}

	pcap_loop(pcap_handle,-1,callback_packet_caught,NULL);

	pcap_close(pcap_handle); 


};

void callback_packet_caught(u_char *usr_args, const struct pcap_pkthdr *cap_pckt_header, const u_char *cap_pckt) {
	
	int tcp_header_len,total_header_size,total_data_size;
	u_char *in_pckt_ptr;
	
	
	in_pckt_ptr=cap_pckt;
	decode_ethernet(in_pckt_ptr);
	in_pckt_ptr+=sizeof(struct ether_hdr);
	decode_ip(in_pckt_ptr);
	in_pckt_ptr+sizeof(struct ip_hdr);
	tcp_header_len=decode_tcp(in_pckt_ptr);
	
	in_pckt_ptr+=tcp_header_len;
	total_header_size=in_pckt_ptr-cap_pckt;
	total_data_size=cap_pckt_header->len-total_header_size;
	if ((ntohs(tcp_hdr0.tcp_src_port)==6666) ||  (ntohs(tcp_hdr0.tcp_dest_port)==6666)) {
		printf("sniff");
		print_packet(in_pckt_ptr,total_data_size,cap_pckt_header->len);
	} else {
		printf("\nnon-sniff:%d",ntohs(tcp_hdr0.tcp_src_port));
	}
}

void decode_ethernet(const u_char *eth_header_start) {
	struct ether_hdr *ether_hdr1;
	ether_hdr1=(struct ether_hdr*) eth_header_start;
	for (int i=0;i<ETHER_ADDR_LEN;i++) 
		ether_hdr0.ether_src_addr[i]=ether_hdr1->ether_src_addr[i];
	for (int i=0;i<ETHER_ADDR_LEN;i++) 
		ether_hdr0.ether_dest_addr[i]=ether_hdr1->ether_dest_addr[i];
	
	ether_hdr0.ether_type=ether_hdr1->ether_type;

// #define ETHER_ADDR_LEN 6  //MAC address- 6 bytes
// #define ETHER_HDR_LEN 14  //2 MAC addresses plus ethernet type 2 bytes

// struct ether_hdr {
//         unsigned char ether_dest_addr[ETHER_ADDR_LEN];  //destination MAC address
//         unsigned char ether_src_addr[ETHER_ADDR_LEN];   //source MAC address
//         unsigned short ether_type;                      //type of ethernet packet
// };


}

void print_packet(u_char *in_pckt_ptr0,int total_data_size0,int pckt_header_len0) {
	printf("\n\n--------> PACKET CAUGHT:%d bytes ---------------------------------------------------\n ",pckt_header_len0);
	printf("\n          --------> ETHERNET HEADER: 14 bytes ----------------------------------------");
	printf("\n          SOURCE MAC: %02x",ether_hdr0.ether_src_addr[0]);
	for (int i=1;i<ETHER_ADDR_LEN;i++) 
		printf(":%02x",ether_hdr0.ether_src_addr[i]);
	printf("\n          DEST MAC:   %02x",ether_hdr0.ether_dest_addr[0]);
	for (int i=1;i<ETHER_ADDR_LEN;i++) 
		printf(":%02x",ether_hdr0.ether_dest_addr[i]);
	printf("\n          TYPE:       %hu\n",ether_hdr0.ether_type);
		

	printf("\n                    --------> IP HEADER: 20 bytes ----------------------------------------");
	printf("\n                    SOURCE IP:       %s",inet_ntoa(*(struct in_addr*)&ip_hdr0.ip_src_addr));
	printf("\n                    DEST IP:         %s",inet_ntoa(*(struct in_addr*)&ip_hdr0.ip_dest_addr));
	printf("\n                    ID:              %d",ip_hdr0.ip_id);
	printf("\n                    TYPE OF SERVICE: %d",ip_hdr0.ip_tos);
	printf("\n                    LENGTH:          %d",ntohs(ip_hdr0.ip_len));
	printf("\n                    FRAGMENT OFFSET: %d",ntohs(ip_hdr0.ip_frag_offset));
	printf("\n                    TIME TO LIVE:    %d",ip_hdr0.ip_ttl);
	printf("\n                    PROTOCOL TYPE:   %d",ip_hdr0.ip_type);
	printf("\n                    CHECKSUM:        %d",ntohs(ip_hdr0.ip_checksum));
	printf("\n                    IP VERSION:      %d",ip_hdr0.ip_version_and_header_length & 0x0F);
	printf("\n                    HEADER LENGTH:   %d\n",ip_hdr0.ip_version_and_header_length & 0xF0);
	
	printf("\n                              --------> TCP HEADER: 32 bytes ----------------------------------------");
	printf("\n                              SOURCE PORT:    %d",ntohs(tcp_hdr0.tcp_src_port));
	printf("\n                              DEST PORT:      %d",ntohs(tcp_hdr0.tcp_dest_port));
	printf("\n                              SEQUENCE NR:    %d",ntohl(tcp_hdr0.tcp_seq));
	printf("\n                              ACKNOWLEDGE NR: %d",ntohl(tcp_hdr0.tcp_ack));
	printf("\n                              OFFSET:         %d",tcp_hdr0.tcp_offset);
	printf("\n                              RESERVED:       %d",tcp_hdr0.reserved);
	printf("\n                              TCP WINDOW:     %d",ntohs(tcp_hdr0.tcp_window));
	printf("\n                              CHECKSUM:       %d",ntohs(tcp_hdr0.tcp_checksum));
	printf("\n                              URGENT:         %d",ntohs(tcp_hdr0.tcp_urgent));
	printf("\n                              FLAGS:          ");
	if (tcp_hdr0.tcp_flags & TCP_FIN) printf ("FIN ");
	if (tcp_hdr0.tcp_flags & TCP_SYN) printf ("SYN ");
	if (tcp_hdr0.tcp_flags & TCP_RST) printf ("RST ");
	if (tcp_hdr0.tcp_flags & TCP_PUSH) printf ("PSH ");
	if (tcp_hdr0.tcp_flags & TCP_ACK) printf ("ACK ");
	if (tcp_hdr0.tcp_flags & TCP_URG) printf ("URG ");

	printf("\n\n                                        --------> PACKET DATA: size:%d bytes\n",total_data_size0);
	if(total_data_size0) {
		printf("\n");
		dump(in_pckt_ptr0,total_data_size0,40);
	}
	else
		printf("\n\n                                NO DATA");
}
void decode_ip(const u_char *ip_header_start) {
	struct ip_hdr *ip_hdr1;
	ip_hdr1=(struct ip_hdr *)ip_header_start;

	ip_hdr0.ip_version_and_header_length=ip_hdr1->ip_version_and_header_length;
	ip_hdr0.ip_tos=ip_hdr1->ip_tos;
	ip_hdr0.ip_len=ip_hdr1->ip_len;
	ip_hdr0.ip_id=ip_hdr1->ip_id;
	ip_hdr0.ip_frag_offset=ip_hdr1->ip_frag_offset;
	ip_hdr0.ip_ttl=ip_hdr1->ip_ttl;
	ip_hdr0.ip_type=ip_hdr1->ip_type;
	ip_hdr0.ip_checksum=ip_hdr1->ip_checksum;
	ip_hdr0.ip_src_addr=ip_hdr1->ip_src_addr;
	ip_hdr0.ip_dest_addr=ip_hdr1->ip_dest_addr;

	

//      unsigned char ip_version_and_headre_length;     //1 BYTE vearsion and header length (2 values in one byte)
//      unsigned char ip_tos;                           //1 BYTE type of service
//      unsigned short ip_len;                          //2 BYTES total length
//      unsigned short ip_id;                           //2 BYTES id number
//      unsigned short ip_frag_offset;                  //2 BYTES fragment offset and flags (2 bytes)
//      unsigned char ip_ttl;                           //1 BYTE time to live for the packet
//      unsigned char ip_type;                          //1 BYTE protocol type//
//      unsigned short ip_checksum;                     //2 BYTES checksum
//      unsigned int ip_src_addr;                       //4 BYTES ip address of the source
//      unsigned int ip_dest_addr;                      //4 BYTES ip destination address

}

int decode_tcp(const u_char *tcp_header_start) {
	struct tcp_hdr *tcp_hdr1;
	tcp_hdr1=(struct tcp_hdr *)tcp_header_start;

	tcp_hdr0.tcp_src_port=tcp_hdr1->tcp_src_port;
	tcp_hdr0.tcp_dest_port=tcp_hdr1->tcp_dest_port;
	tcp_hdr0.tcp_seq=tcp_hdr1->tcp_seq;
	tcp_hdr0.tcp_ack=tcp_hdr1->tcp_ack;
	tcp_hdr0.reserved=tcp_hdr1->reserved;
	tcp_hdr0.tcp_offset=tcp_hdr1->tcp_offset;
	tcp_hdr0.tcp_flags=tcp_hdr1->tcp_flags;
	tcp_hdr0.tcp_window=tcp_hdr1->tcp_window;
	tcp_hdr0.tcp_checksum=tcp_hdr1->tcp_checksum;
	tcp_hdr0.tcp_urgent=tcp_hdr1->tcp_urgent;


//        unsigned short tcp_src_port;                    //2 BYTES source port
//        unsigned short tcp_dest_port;                   //2 BYTES destination port
//        unsigned int tcp_seq;                           //4 BYTES tcp sequence number
//        unsigned int tcp_ack;                           //4 BYTES tcp acknowledgement number
//        unsigned char reserved:4;                       //4 BITS from 6 bits of reserved field
//        unsigned char tcp_offset:4;                     //4 BITS for tcp offset for little-endian host
//        unsigned char tcp_flags;                        //1 BYTE (6 bits of a byte) for tcp flags;
// #define TCP_FIN 0x01
// #define TCP_SYN 0x02
// #define TCP_RST 0x04
// #define TCP_PUSH 0x08
// #define TCP_ACK 0x10
// #define TCP_URG 0x20
//        unsigned short tcp_window;                      //2 BYTES tcp window
//        unsigned short tcp_checksum;                    //2 BYTES tcp checksum
//        unsigned short tcp_urgent;                      //2 BYTES tcp urgent pointer

}



