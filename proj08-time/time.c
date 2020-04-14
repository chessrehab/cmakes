#include "start01.h"
#include <sys/time.h>
#include <time.h>
#include <locale.h>

#define MAX_BUF 100
#define PATH01 "/home/marty/cmakes/proj08-time/data/test01.dat"
#define PATH02 "/home/marty/cmakes/proj08-time/data/test02.dat"
#define PATH03 "/home/marty/cmakes/proj08-time/data/test03.dat"

int main() {
	clock_t cas1=clock();

	struct timeval *tv=malloc(sizeof(tv));
	memset(tv,0,sizeof(tv));
	if(gettimeofday(tv,NULL)==-1) errExit("gettimeofday");
	printf("\ngettimeofday returns:%d\n",(int)tv->tv_sec); 
	free(tv);
	sleep(2);
	time_t t=time(NULL);
	printf("time returns:%d\n",(int)t);
	printf("ctime returns:%s\n",ctime(&t));
	struct tm *tm=gmtime(&t);
	struct tm *tm2=localtime(&t);
	printf("\ngmtime returns:%d:%d:%d",tm->tm_hour,tm->tm_min,tm->tm_sec);
	printf("\nlocaltime returns:%d:%d:%d\n",tm2->tm_hour,tm2->tm_min,tm2->tm_sec);

	time_t t2=mktime(tm2);
	printf("mktime returns:%d\n",(int)t2);

	printf("asctime returns:%s\n",asctime(tm2));	 

	char out[100];
	size_t s=strftime(out,100,"strftime returns:%F\n",tm2);
	printf(out);	 
	char *x;
	x=setlocale(LC_TIME,NULL);
	printf("\nLocale is:%s\n",x);
	clock_t cas2=clock();
	
	printf("\ncas1:%d\n",cas1);
	printf("\ncas2:%d\n",cas2);
	printf("\nrozdiel:%d\n",cas2-cas1);
	
	
}




