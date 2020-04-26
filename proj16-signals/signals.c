#include "start01.h"
#include <signal.h>
#define MAX_BUF 100
#define PATH01 "/home/martyx/cmakes/proj16-signals/data/test01.dat"
#define PATH02 "/home/martyx/cmakes/proj16-signals/data/test02.dat"
#define PATH03 "/home/martyx/cmakes/proj16-signals/data/test03.dat"

void handler1(int s) {
	printf("\nsignal recieved:%o\nsignal desc:%s\n",s,strsignal(s));
	psignal(s,"msg desc disgnal:");
}

int main() {
	void (*fc_pointer)(int)=signal(2,handler1);
    	while(1);

}




