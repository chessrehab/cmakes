//socket functions:
//1. CREATE A NEW SOCKET
int socket(int domain, int type, int protocol);
//creates new socket, returns and fd or -1 on error

DOMAINS: (protocol family groups)
#define PF_UNSPEC	0	Unspecified.  
#define PF_LOCAL	1	/* Local to host (pipes and file-domain). 
#define PF_UNIX		PF_LOCAL /* POSIX name for PF_LOCAL. 
#define PF_FILE		PF_LOCAL /* Another non-standard name for PF_LOCAL. 
#define PF_INET		2	/* IP protocol family. 
#define PF_AX25		3	/* Amateur Radio AX.25. 
#define PF_IPX		4	/* Novell Internet Protocol. 
#define PF_APPLETALK	5	/* Appletalk DDP.  
#define PF_NETROM	6	/* Amateur radio NetROM.  
#define PF_BRIDGE	7	/* Multiprotocol bridge.  
#define PF_ATMPVC	8	/* ATM PVCs.  
#define PF_X25		9	/* Reserved for X.25 project.  
#define PF_INET6	10	/* IP version 6.  
#define PF_ROSE		11	/* Amateur Radio X.25 PLP.  
#define PF_DECnet	12	/* Reserved for DECnet project.  
#define PF_NETBEUI	13	/* Reserved for 802.2LLC project.  
#define PF_SECURITY	14	/* Security callback pseudo AF.  
#define PF_KEY		15	/* PF_KEY key management API.  
#define PF_NETLINK	16
#define PF_ROUTE	PF_NETLINK /* Alias to emulate 4.4BSD.  
#define PF_PACKET	17	/* Packet family.  
#define PF_ASH		18	/* Ash.  
#define PF_ECONET	19	/* Acorn Econet.  
#define PF_ATMSVC	20	/* ATM SVCs.  
#define PF_RDS		21	/* RDS sockets.  
#define PF_SNA		22	/* Linux SNA Project 
#define PF_IRDA		23	/* IRDA sockets.  
#define PF_PPPOX	24	/* PPPoX sockets.  
#define PF_WANPIPE	25	/* Wanpipe API sockets.  
#define PF_LLC		26	/* Linux LLC.  
#define PF_IB		27	/* Native InfiniBand address.  
#define PF_MPLS		28	/* MPLS.  
#define PF_CAN		29	/* Controller Area Network.  
#define PF_TIPC		30	/* TIPC sockets.  
#define PF_BLUETOOTH	31	/* Bluetooth sockets.  
#define PF_IUCV		32	/* IUCV sockets.  
#define PF_RXRPC	33	/* RxRPC sockets.  
#define PF_ISDN		34	/* mISDN sockets.  
#define PF_PHONET	35	/* Phonet sockets.  
#define PF_IEEE802154	36	/* IEEE 802.15.4 sockets.  
#define PF_CAIF		37	/* CAIF sockets.  
#define PF_ALG		38	/* Algorithm sockets.  
#define PF_NFC		39	/* NFC sockets.  
#define PF_VSOCK	40	/* vSockets.  
#define PF_KCM		41	/* Kernel Connection Multiplexor. 
#define PF_QIPCRTR	42	/* Qualcomm IPC Router.  
#define PF_SMC		43	/* SMC sockets.  
#define PF_XDP		44	/* XDP sockets.  
#define PF_MAX		45	/* For now..  

TYPES: (type of sockets)
enum socket_type {
	SOCK_STREAM =1,
	SOCK_DGRAM =2,
	...
}

PROTOCOL: (exact protocol from the protocol family)
	//usually only one protocol in a family so enum index 0 should do

//2. ADJUST SOCKET OPTIONS
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
//returns 0 on success or -1 on error
LEVEL: (level of socket, in our case will be SOL_SOCKET)

#define SOL_RAW		255
#define SOL_DECNET      261
#define SOL_X25         262
#define SOL_PACKET	263
#define SOL_ATM		264	// ATM layer (cell level).  
#define SOL_AAL		265	// ATM Adaption Layer (packet level).  
#define SOL_IRDA	266
#define SOL_NETBEUI	267
#define SOL_LLC		268
#define SOL_DCCP	269
#define SOL_NETLINK	270
#define SOL_TIPC	271
#define SOL_RXRPC	272
#define SOL_PPPOL2TP	273
#define SOL_BLUETOOTH	274
#define SOL_PNPIPE	275
#define SOL_RDS		276
#define SOL_IUCV	277
#define SOL_CAIF	278
#define SOL_ALG		279
#define SOL_NFC		280
#define SOL_KCM		281
#define SOL_TLS		282
#define SOL_XDP		283

OPTNAME: (option itself- in our case SO_REUSEADDR)
OPTVAL: (option value address, in our case and adress of static int)
OPTLEN: (size of the data value, in ur case its int so sizeof int)


//3. CONNECT A SOCKET TO A REMOTE HOST ADDRESS
int connect(int fd, struct sockaddr *remote_host, socklen_t addr_length);
//return 0 on success or -1 on error
//generic sockaddr address structure
struct sockaddr
  {
    __SOCKADDR_COMMON (sa_);	 //Common data: address family and length. Will be  unsigned short
    char sa_data[14];		 //Address data
  };


//internet specific sockaddr structure
struct sockaddr_in
  {
    __SOCKADDR_COMMON (sin_);		//Common data: address family and length. Will be  unsigned short wth a name sin_family
    in_port_t sin_port;			// Port number.
    struct in_addr sin_addr;		// Internet address

    // Pad to size of `struct sockaddr'.  
    unsigned char sin_zero[sizeof (struct sockaddr)
			   - __SOCKADDR_COMMON_SIZE
			   - sizeof (in_port_t)
			   - sizeof (struct in_addr)];
  };

//internet address value structure
typedef uint32_t in_addr_t;
struct in_addr
  {
    in_addr_t s_addr;
  };

//byte ordering functions (network and host endianness)
htonl(long) //host to network long (4 bytes)
htons(short) //host to network short (2 bytes)
ntohl(long) //network to host long (4 bytes)\
ntohs(short) //network to host short (2 bytes)
void inet_aton (char *ascii, struct in_addr *network_addr) //converst sccii IP to network address struct
char *inet ntoa (struct in_addr *newtork_addr) //returns ascii IP address

//4. BIND SOCKET TO LOCAL ADDRESS
int bind(int fd, struct sockaddr *local_addr, socklen_t addr_length);
//returns 0 on success or -1 on error

//5.LISTEN FOR INCOMING CONNECTIONS
int listen(int fd, int backlog_queue_size);
//returns 0 on success or -1 on error
//listens for incoming connections and queues the connection requests to queue size

//6.ACCEPT CONNECTION
int accept(int fd, sockaddr *remote host, socklen_t *addr_length);
//returns fd for established connection socket
//after accepting will fill sockaddr sructure with remote  connected device data and the size of the structure in addr_length

//7.SEND PACKETS TO A SOCKET
int send(int fd, void *buffer, size_t n, int flags);
//returns number of bytes sent to socket from buffer or -1 on error

//8.RECIEVE PACKETS
int recv(int fd, void *buffer, size_t n, int flags);
//returns number of bytes recieved from the socket to the buffer or -1 on error



//STRUCTURES FOR PACKET HEADERS

//1.ETHERNET protocol (data link OSI layer)
#define ETHER_ADDR_LEN 6
#define ETHER_HDR_LEN 14 

//14 bytes overall- fixed size
struct ether_hdr {
	unsigned char ether_dest_addr[ETHER_ADDR_LEN]; //destination MAC address (6 bytes)
	unsigned char ether_src_addr[ETHER_ADDR_LEN]; //source MAC address (6 bytes)
	unsigned short ether_type; //type pf ethernet paclet (2 bytes)
};

//2. IP protocol (network OSI layer)

//20 bytes total - fixed size
struct ip_hdr {
	unsigned char ip_version_and_header_length; //version and header length (1 byte)
	unsigned char ip_tos; //type of service (1 byte)
	unsigned short ip_len; //total length (2 bytes)
	unsigned short ip_id; //identification number(2 bytes)
	unsigned char ip_ttl; //time to live (1 byte)
	unsigned char ip_type; //protocol type (1 byte)
	unsigned short ip_checksum; //checksum (2 bytes)
	unsigned int ip_src_addr; //source ip address (4 bytes)
	unsigned int ip_dest_addr; //destination ip address (4 bytes)
};

//3. TCP protocol (transport layer OSI)
//data oddest field carries the variable size of the TCP header - not fixed size- carefull about endianness

struct tcp_hdr {
	unsigned short tcp_src_port; //source tcp port
	unsigned short tcp_dest_port; //destination tcp port
	unsigned int tcp_seq; //TCP sequence number
	unsigned int tcp_ack; //TCP acknoledgement number
	unsigned char reserved:4; //4 bits of 6 bits of reserved space
	unsigned char tcp_offset:4; //TCP data offset for little endian host
	unsigned char tcp_flags; //TCP flags
#define TCP_FIN	0x01
#define TCP_SYN 0x02
#define TCP_RST 0x04
#define TCP_PUSH 0x08
#define TCP_ACK 0x10
#define TCP_URG 0x20
	unsigned short tcp_window; //TCP window size
	unsigned short tcp_checksum; //TCP checksum
	unsigned short tcp_urgent; //TCP urgent pointer
}


