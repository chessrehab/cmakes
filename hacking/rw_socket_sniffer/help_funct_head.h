


//error message
void fatal(char *);

//dumping the data buffer from the packet to hex and to ascii chars
void dump(const unsigned char *, const unsigned int);

//sending strings to a socket with check on all bytes being sent
int send_string_tosocket(int, unsigned char *);

//recieving strings from socket
int recv_line(int, unsigned char *);




//structure for ethernet header
#define ETHER_ADDR_LEN 6  //MAC address- 6 bytes
#define ETHER_HDR_LEN 14  //2 MAC addresses plus ethernet type 2 bytes

struct ether_hdr {
	unsigned char ether_dest_addr[ETHER_ADDR_LEN];  //destination MAC address
	unsigned char ether_src_addr[ETHER_ADDR_LEN];	//source MAC address
	unsigned short ether_type;			//type of ethernet packet
};

//structure for ip header
struct ip_hdr {
	unsigned char ip_version_and_headre_length;	//1 BYTE vearsion and header length (2 values in one byte)
	unsigned char ip_tos;				//1 BYTE type of service
	unsigned short ip_len;				//2 BYTES total length
	unsigned short ip_id;				//2 BYTES id number
	unsigned short ip_frag_offset;			//2 BYTES fragment offset and flags (2 bytes)
	unsigned char ip_ttl;				//1 BYTE time to live for the packet
	unsigned char ip_type;				//1 BYTE protocol type
	unsigned short ip_checksum;			//2 BYTES checksum
	unsigned int ip_src_addr;			//4 BYTES ip address of the source
	unsigned int ip_dest_addr;			//4 BYTES ip destination address
};

//structure of tcp header
struct tcp_hdr {
	unsigned short tcp_src_port;			//2 BYTES source port
	unsigned short tcp_dest_port;			//2 BYTES destination port
	unsigned int tcp_seq;				//4 BYTES tcp sequence number
	unsigned int tcp_ack;				//4 BYTES tcp acknowledgement number
	unsigned char reserved:4;			//4 BITS from 6 bits of reserved field
	unsigned char tcp_offset:4;			//4 BITS for tcp offset for little-endian host
	unsigned char tcp_flags;			//1 BYTE (6 bits of a byte) for tcp flags;
#define TCP_FIN 0x01
#define TCP_SYN 0x02
#define TCP_RST 0x04
#define TCP_PUSH 0x08
#define TCP_ACK 0x10
#define TCP_URG 0x20
	unsigned short tcp_window;			//2 BYTES tcp window
	unsigned short tcp_checksum;			//2 BYTES tcp checksum
	unsigned short tcp_urgent;			//2 BYTES tcp urgent pointer
};


