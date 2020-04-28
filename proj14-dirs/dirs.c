#define _XOPEN_SOURCE 600
#include "start01.h"
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>
#include <ftw.h>



#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj14-dirs/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj14-dirs/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj14-dirs/data/test03.dat"
#define PATH04 "/home/marty/cmakes/proj14-dirs/data/test01-hl2"
#define PATH05 "/home/marty/cmakes/proj14-dirs/data/renamed_test01-hl2"
#define PATH06 "/home/marty/cmakes/proj14-dirs/data/symlink_to_renamed_test01-hl2"
#define PATH07 "/home/marty/cmakes/proj14-dirs/data/nw_folder"
#define PATH08 "/home/marty/cmakes/proj14-dirs/data/temp_folder2/"
#define PATH09 "/home/marty/cmakes/proj14-dirs/data/temp_folder2/tmp1.dat"
#define PATH10 "/home/marty/cmakes/proj14-dirs/data/temp_folder2/tmp2.dat"
#define PATH11 "/home/marty/cmakes/proj14-dirs/data/temp_folder2/tmp3.dat"
#define PATH12 "/home/marty/cmakes/proj14-dirs/data/temp_folder2/tmp1-hl.dat"
#define PATH13 "/home/marty/cmakes/proj14-dirs/data/temp_folder2/tmp1-hl-syml.dat"
#define PATH14 "/home/marty/cmakes/proj14-dirs/data/temp_folder2/temp_fl2"
#define PATH15 "/home/marty/cmakes/proj14-dirs/"

typedef int (*vypis_t)(const char*,const  struct stat *, int , struct FTW *);

int vypis(const	char*pathname1,const  struct stat *stat1, int type, struct FTW *ftwb) {
	printf("\n %*s%s",4 * ftwb->level," ",pathname1);
	printf("\n%*sST_DEV:%o\n",5 * ftwb->level," ",stat1->st_dev);
	printf("%*sST_INO:%d\n",5 * ftwb->level," ",stat1->st_ino);
	printf("%*sST_MODE:%s\n",5 *ftwb->level," ",(stat1->st_mode & S_IFDIR)? "directory": "file");
//	printf("-----------------------------\n");
//	printf("FTW type:%o\n",type);
//	printf("FTW:\nbase:%d\nlevel:%d\n",ftwb->base,ftwb->level);
//	printf("..............................................\n");
	return 0;
}

int main() {
	if(link(PATH01,PATH04)==-1) {
		unlink(PATH04);
		link(PATH01,PATH04);
	}
	
	printf("\nfile %s hard linked..\n",PATH04);

	rename(PATH04,PATH05);
	symlink(PATH05,PATH06);
	char buf[MAX_BUF];
	ssize_t b_read=readlink(PATH06,(char *) &buf,MAX_BUF);
	printf("\nread name of symlink: %s\nread %d bytes\n",(char *) &buf,(int)b_read);	
	mkdir(PATH07,S_IRUSR|S_IWUSR|S_IXUSR);
	mkdir(PATH08,S_IRUSR|S_IWUSR|S_IXUSR);
	rmdir(PATH07);
	remove(PATH06);
	creat(PATH09,S_IRUSR|S_IWUSR);
	creat(PATH10,S_IRUSR|S_IWUSR);
	creat(PATH11,S_IRUSR|S_IWUSR);
	link(PATH09,PATH12);
	symlink(PATH12,PATH13);
	mkdir(PATH14,S_IRUSR|S_IWUSR|S_IXUSR);
	
	DIR *dirstr=opendir(PATH08);
	struct dirent *dirent1;
	while ((dirent1=readdir(dirstr))!=NULL) {
		printf("\nread_entry_inode:%d\nentry_name:%s\n",(int) dirent1->d_ino,dirent1->d_name);
	}
	printf("\n...................................................................................................................\n");
	rewinddir(dirstr);
	struct stat *s=malloc(sizeof(struct stat));
	char dirname1[255];
	while ((dirent1=readdir(dirstr))!=NULL) {
		if(strcmp(dirent1->d_name,".")!=0 && strcmp(dirent1->d_name,"..")!=0) {
			printf("\nread_entry_inode:%d\nentry_name:%s",(int) dirent1->d_ino,dirent1->d_name);
			sprintf(dirname1,"%s/%s\0",dirname(strdup(PATH09)),dirent1->d_name);
			printf("\nfull_path:%s\n",dirname1);
			stat(dirname1,s);
			printf("\nST_DEV:%o\n",s->st_dev);
			printf("ST_INO:%d\n",s->st_ino);
			printf("ST_MODE:%s\n",(s->st_mode & S_IFDIR)? "directory": "file");
			printf("-----------------------------\n");
		}
	}
	
	
	int ntf=nftw(PATH15,vypis,20,0);
	printf("\n\nsize of function is:%d\n",sizeof(vypis_t));
	printf("\n\nsize of char* is:%d\n",sizeof(char *));
	
	closedir(dirstr);	
}




