#include "start01.h"

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj03-files/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj03-files/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj03-files/data/test03.dat"

int main() {
    
    char buf[MAX_BUF];
    ssize_t w_bytes,r_bytes;
    int fdr,fdw,fdt;
    struct iovec siov[4];
    int extra1;
    char extra2[5];

    int x=65;
    char retaz[]="retaz";
    
    siov[0].iov_base=&retaz;
    siov[0].iov_len=5;
    siov[1].iov_base=&x;
    siov[1].iov_len=sizeof(int);
    siov[2].iov_base=&extra2;
    siov[2].iov_len=5;
    siov[3].iov_base=&extra1;
    siov[3].iov_len=sizeof(int);	

//x
    
	
    
    printf("...starting...\n");
    
    if((fdr=open(PATH01, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR))==-1) errExit("open for read error");
    printf("........opened file test01.dat for rw\n");
    if(ftruncate(fdr,0)==-1) errExit("error truncating the test01.dat");
    
    if((fdw=open(PATH02,O_RDWR | O_CREAT,S_IRUSR | S_IWUSR))==-1)  errExit("open for write to test02.dat error");
    printf("........opened file test02.dat for rw\n");
    if(ftruncate(fdw,0)==-1) errExit("error truncating the test02.dat");

    char tmpbuf[] ="temporaryXXXXXX";
    printf("........opening tempfile %s for rw\n",tmpbuf);
    if((fdt=mkstemp(tmpbuf))==-1) errExit("error on opening temp");
    printf("........opened tempfile %s for rw\n",tmpbuf);

    int fg=fcntl(fdr,F_GETFL);
    if (fg==-1) errExit("error reading the flags");
    printf("read the flags of file test01.dat as \n decimal: %d\n hexadecimal: 0x%x\n octal: 0%o\n",fg,fg,fg);
    
    int newfg=fg | O_APPEND;

    fg=fcntl(fdr,F_SETFL,newfg);
    if (fg==-1) errExit("error writing new flags");
    printf("wrote the flags of file test01.dat as \n decimal: %d\n hexadecimal: 0x%x\n octal: 0%o\n",fg,fg,fg);

    fg=fcntl(fdr,F_GETFL);
    if (fg==-1) errExit("error on second reading the flags");
    printf("read the flags of file test01.dat second time  as \n decimal: %d\n hexadecimal: 0x%x\n octal: 0%o\n",fg,fg,fg);

    	

    w_bytes=write(fdr,"hello there!\n I am here...\0",50);
    if (w_bytes==-1) errExit("error writing initial temp01");
    
    r_bytes=pread(fdr,buf,5,7);
    if (r_bytes==-1) errExit("error reading position  temp01");
    
    
    w_bytes=write(fdw,"Ahoj..\n\0",10);
    if (w_bytes==-1) errExit("error writing initial in temp02");

    w_bytes=pwrite(fdw,buf,7,12);
    if (w_bytes==-1) errExit("error writing position in temp02");

    w_bytes=pwritev(fdt,siov,2,0);
    if(w_bytes==-1) errExit("error writing structures to temp file");
    
    r_bytes=preadv(fdt,siov+2,2,0);
    if(r_bytes==-1) errExit("error reading structures from temp file");

    (*((int*)(siov[3].iov_base)))++;
    
    w_bytes=pwritev(fdr,siov,4,0);
    if(w_bytes==-1) errExit("error on positioned write");
  
    
    
   
	 
    if(close(fdr)==-1) errExit("error on closing the file test01.dat");
        printf("...closed file test01.dat\n");

    if (close(fdw)==-1) errExit("error on closing the file test02.dat") ;
    printf("...closed file test02.dat\n");

    if (close(fdt)==-1) errExit("error on closing the temp file") ;
    printf("...closed temp file\n");	
    
    printf("Exiting...all went well, have a good day!\n");

}




