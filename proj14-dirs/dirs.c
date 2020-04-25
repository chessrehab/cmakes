#include "start01.h"
#include <sys/stat.h>
#include <dirent.h>

#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj14-dirs/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj14-dirs/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj14-dirs/data/test03.dat"
#define PATH04 "/home/martyx/cmakes/proj14-dirs/data/test01-hl2"
#define PATH05 "/home/martyx/cmakes/proj14-dirs/data/renamed_test01-hl2"
#define PATH06 "/home/martyx/cmakes/proj14-dirs/data/symlink_to_renamed_test01-hl2"
#define PATH07 "/home/martyx/cmakes/proj14-dirs/data/nw_folder"
#define PATH08 "/home/martyx/cmakes/proj14-dirs/data/temp_folder2"
#define PATH09 "/home/martyx/cmakes/proj14-dirs/data/temp_folder2/tmp1.dat"
#define PATH10 "/home/martyx/cmakes/proj14-dirs/data/temp_folder2/tmp2.dat"
#define PATH11 "/home/martyx/cmakes/proj14-dirs/data/temp_folder2/tmp3.dat"
#define PATH12 "/home/martyx/cmakes/proj14-dirs/data/temp_folder2/tmp1-hl.dat"
#define PATH13 "/home/martyx/cmakes/proj14-dirs/data/temp_folder2/tmp1-hl-syml.dat"
#define PATH14 "/home/martyx/cmakes/proj14-dirs/data/temp_folder2/temp_fl2"



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
	printf("\n....................................................................................\n");
	rewinddir(dirstr);
	while ((dirent1=readdir(dirstr))!=NULL) {
		printf("\nread_entry_inode:%d\nentry_name:%s\n",(int) dirent1->d_ino,dirent1->d_name);
	}
	
	closedir(dirstr);	
}




