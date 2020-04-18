#include "start01.h"
#include <sys/mount.h>
#include <sys/statvfs.h>


#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj11-filesys/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj11-filesys/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj11-filesys/data/test03.dat"
static void usageError(const char *progName,const char *msg) {
	if (msg!=NULL) fprintf(stderr,"%s",msg);
	fprintf(stderr,"Usage: %s [options] source target\n\n",progName);
	fprintf(stderr,"Availablle options:\n");
#define fpe(str) fprintf(stderr,"   " str)
	fpe("-t fstype   [e.g., 'ext2' or reiserfs']\n");
	fpe("-o data    [filesystem-dependent options,\n");
	fpe("		 e.g., 'bsdgroups' for ext2]\n");
	fpe("-f mountflags  can include any of:\n");
#define fpe2(str) fprintf(stderr,"			" str)
	fpe2("b - MS_BIND	create a bind mount\n");
	fpe2("d - MS_DIRSYNC	synchronous directory updates\n");
	fpe2("l - MS_MANDLOCK	permit mandatory locking\n");
	fpe2("m - MS_MOVE	automatically move subtree\n");
	fpe2("A - MS_NOATIME	dont update A time(last access time\n");
	fpe2("V - MS_NODEV	dont permit device access\n");
	fpe2("D - MS_NODIRATIME	dont update atime on directories\n");
	fpe2("E - MS_NOEXEC	dont allow executables\n");
	fpe2("S - MS_NOSUID	disable set-user id\n");
	fpe2("r - MS_RDONLY	read-only mount\n");
	fpe2("c - MS_REC	recursive mount\n");
	fpe2("R - MS_REMOUNT	remount\n");
	fpe2("s - MS_SYNCHRONOUS make writes synchronous\n");
	exit(EXIT_FAILURE);
}




int main(int argc,char *argv[]) {


	unsigned long flags;
	char *data,*fstype;
	int j,opt;
	struct statvfs *stfs=malloc(sizeof(struct statvfs));
	flags=0;
	data=NULL;
	fstype=NULL;

	 while((opt=getopt(argc,argv,"o:t:f:"))!=-1) {
		switch(opt) {
			case 'o':
				data=optarg;
				break;
			case 't':
				fstype=optarg;
				break;
			case 'f':
				
				for(j=0;j < strlen(optarg);j++) {
					switch(optarg[j]) {
						printf("\optarg%d:%c\n",j,optarg[j]);
						case 'b':flags |= MS_BIND; break;
						case 'd':flags |= MS_DIRSYNC; break;
						case 'l':flags |= MS_MANDLOCK; break;
						case 'm':flags |= MS_MOVE; break;
						case 'A':flags |= MS_NOATIME; break;
						case 'V':flags |= MS_NODEV; break;
						case 'D':flags |= MS_NODIRATIME; break;
						case 'E':flags |= MS_NOEXEC; break;
						case 'S':flags |= MS_NOSUID; break;
						case 'r':flags |= MS_RDONLY; break;
						case 'c':flags |= MS_REC; break;
						case 'R':flags |= MS_REMOUNT; break;
						case 's':flags |= MS_SYNCHRONOUS; break;
						default: usageError(argv[0],NULL);
					}
				}
				break;
			default: usageError(argv[0],NULL);
			}
	}
	if (argc != optind +2) usageError(argv[0],"Wrong number of args\n");
	printf("\nRESULTING COMMAND:mount(%s,%s,%s,%o,%s)\n",argv[optind],argv[optind+1],fstype,flags,data);
	if(statvfs("/",stfs)!=0) errExit("structure fs error");
	printf("\nfs block size:%d\n",stfs->f_bsize);
	printf("fs fundamental block size:%d\n",stfs->f_frsize);
	printf("fs total nr blocks:%d\n",stfs->f_blocks);
	printf("fs total nr free blocks:%d\n",stfs->f_bfree);
	printf("fs total nr available blocks for unprivileged proc:%d\n",stfs->f_bavail);
	printf("fs total nr inodes:%d\n",stfs->f_files);
	printf("fs total nr free inodes:%d\n",stfs->f_ffree);
	printf("fs total nr free inodes for upriviliged proc:%d\n",stfs->f_favail);
	printf("fs ID:%d\n",stfs->f_fsid);
	printf("fs mount flags:%o\n",stfs->f_flag);
	printf("fs maximum length filenames:%d\n",stfs->f_namemax);

}




