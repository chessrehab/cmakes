#include "start01.h"
#include <sys/inotify.h>

#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj15-filnotif/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj15-filnotif/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj15-filnotif/data/test03.dat"

int main() {
	int fd1=inotify_init();
	int wd1=inotify_add_watch(fd1,PATH01,IN_ALL_EVENTS);
	char  buf[4096]
		__attribute__ ((aligned(__alignof__(struct inotify_event))));
	char *p;
	struct inotify_event *events;
	while(1) {
		int i= read(fd1,buf,sizeof(buf));
		if (i>0) printf("\nbuffer bytes read:%d\n",i);
		for(p=buf;p<buf+i;p+=sizeof(struct inotify_event)+events->len) {
			events=(struct inotify_event *) buf;
			printf("\nstruct inotify_events.wd=%d\n",events->wd);
			printf("\nstruct inotify_events.mask=%o\n",(int) events->mask);
			printf("\nstruct inotify_events.cookie=%d\n",events->cookie);
			printf("\nstruct inotify_events.name=%s\n", events->name);
			printf("\nstruct inotify_events.len=%d\n",events->len);
			
		}
	}

}




