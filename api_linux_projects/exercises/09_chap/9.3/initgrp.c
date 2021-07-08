//implement initgroup() using setgroup and library functions to read from pwd file




#include <stdio.h>
#include <unistd.h>
//getgroups is covered in unistd.h
#include <stdlib.h>
//calloc is covered in stdlib.h
#include <grp.h>
//struct group covered in grp.h
#include <sys/types.h>
#include <string.h>
//strcmp covered in string.h 


//extern int initgroups(const char *user, gid_t group);

//extern struct group {
  //             char   *gr_name;        /* group name */
    //           char   *gr_passwd;      /* group password */
      //         gid_t   gr_gid;         /* group ID */
        //       char  **gr_mem;         /* NULL-terminated array of pointers
//                                          to names of group members */
          // };
extern void setgrent();
extern void endgrent();
extern struct group * getgrent();

extern int getgroups(int size, gid_t list[]);
extern int setgroups(size_t size, const gid_t *list);
extern struct group *getgrgid(gid_t gid);

int initgroups0(const char *user,gid_t group);

int main(int argc, char *argv[]) {

	struct group *gr_ptr;
	int nr_of_my_groups = getgroups(0,NULL);
	printf("\n number of groups this process is a member is %d \n",nr_of_my_groups);
	
	gid_t *gr_list= calloc(nr_of_my_groups,sizeof(gid_t));

	nr_of_my_groups=getgroups(nr_of_my_groups,gr_list);

	for(int i=0;i<nr_of_my_groups;i++) 
		printf("\n group nr.%d:%s",i,getgrgid(gr_list[i])->gr_name);

	free (gr_list);
	initgroups0(argv[1],0);

	nr_of_my_groups = getgroups(0,NULL);
	printf("\n number of groups this process is a member is %d \n",nr_of_my_groups);
	
	gr_list= calloc(nr_of_my_groups,sizeof(gid_t));

	nr_of_my_groups=getgroups(nr_of_my_groups,gr_list);

	for(int i=0;i<nr_of_my_groups;i++) 
		printf("\n group nr.%d:%s",i,getgrgid(gr_list[i])->gr_name);
	return 0;
}

int initgroups0(const char *user,gid_t group) {
	int ngroupmax=sysconf(_SC_NGROUPS_MAX)+1;
	gid_t *grps=malloc(ngroupmax*sizeof(gid_t));
	struct group* grpent_ptr;
	setgrent();
	int cnt=0;
	while ((grpent_ptr=getgrent())!=NULL) {
		for (char **ent=grpent_ptr->gr_mem; *ent!=NULL;ent++) {
			if (strcmp(*ent,user)==0) {
				grps[cnt]=grpent_ptr->gr_gid;
				cnt++;
			}
		}
	}
	grps[cnt]=group;
	cnt++;
	int set=setgroups(cnt,grps);		
	free(grps);
	return 0;
	


}
