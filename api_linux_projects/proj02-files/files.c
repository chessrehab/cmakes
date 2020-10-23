#include "start01.h"

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj02-files/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj02-files/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj02-files/data/test03.dat"

int main() {
    
    char buf[MAX_BUF];
    ssize_t w_bytes,r_bytes;
    int fdr,fdw,fdt;
	
    
    printf("...starting...\n");
    
    if((fdr=open(PATH01, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR))==-1) {
        errExit("open for read error");
    };
    
    printf("....opened file test01.dat for reading\n");
    
    if((r_bytes=read(fdr,buf,MAX_BUF))==-1) {
            errExit("%d read of test01.dat error",(int) r_bytes);
    };
    
    printf("...read %d bytes from test01.dat to buffer\n", (int) r_bytes);
    buf[r_bytes]='\n';
    if((fdw=open(PATH02,O_RDWR | O_CREAT,S_IRUSR | S_IWUSR))==-1) {
        errExit("open for write to test02.dat error");
    };
    
    printf("....opened file test02.dat for writing\n");
    
    if ((w_bytes=write(fdw,buf,MAX_BUF))==-1) {
            errExit("write error");
    };
    printf ("..written %d bytes to test02.dat\n",(int) w_bytes);
    
    if (lseek(fdr,0,SEEK_END)==-1 ) {
        errExit("lseek error");
    };
    
    printf("....found the end of the fi e test0.dat1\n");
    
    w_bytes=0;
    if ((w_bytes=write(fdr,buf,MAX_BUF))==-1) {
        errExit("write on seek position error") ;
    };
    
    printf("...wrote %d bytes to the end of file test01.dat\n", (int) w_bytes);

    if((fdt=open(PATH03,O_RDWR | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR | S_IRGRP |S_IWGRP | S_IROTH | S_IWOTH))==-1) {
	errExit("error opening third file");
    }
    r_bytes=0;
    w_bytes=0;
    if(lseek(fdw,0,SEEK_SET)==-1) {
	errExit("Erroro on seek in the second file");
    }
    while (((r_bytes=read(fdw,buf,1))==1) && (buf[0]!='\0')) {
	if ((w_bytes=write(fdt,buf,1))==-1) {
		errExit("Write error on third file per char");
	}
    }		
    while(1) {};
    if(close(fdr)==-1) {
        errExit("error on closing the file test01.dat");
    };
    
    printf("...closed file test01.dat\n");
    if (close(fdw)==-1) {
        errExit("error on closing the file for writing") ;
    };
    
    printf("...closed file test02.dat\n");

    if (close(fdt)==-1) {
        errExit("error on closing the third file") ;
    };
    
    printf("...closed file test03.dat\n");	
    
    printf("Exiting...all went well, have a good day!\n");

}




