#include <pthread.h>
#include "start01.h"

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj20-threads/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj20-threads/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj20-threads/data/test03.dat"

static volatile int g1=69;
void * f1(void *in) {
	
	pthread_mutex_t m1=PTHREAD_MUTEX_INITIALIZER;
	printf("\nhello %s\n",(char *) in);
	pthread_mutex_lock(&m1);
	g1++;
	pthread_mutex_unlock(&m1);
	pthread_exit((void *) 89);
}


int main() {
	pthread_t t1,t2,t3;
	char *x="marty";
	char *y="manda";
	void **rt;
	pthread_create(&t1,NULL,f1,(void *) x);
	pthread_create(&t2,NULL,f1,(void *) y);
	pthread_join(t1, rt);
	printf("\nmain thread finished and exiting...local thread returned:%d\n",(int)(*rt));
}




