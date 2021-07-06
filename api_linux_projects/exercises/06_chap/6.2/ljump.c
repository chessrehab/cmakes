//program simulates longjmp into a function that has laready returned which eventually messes up everything



#include <setjmp.h>
#include <stdio.h>
//puts is coverred in stdio.h



void longjump(jmp_buf env, int val);

jmp_buf env;


int f1() {

	if(setjmp(env)==0) {
		puts("\n in function 1 setting up jump point\n");
	}
	else {
		puts("\n in function 1 again..\n");
	}
	return 0;
}

int f2() {
	longjmp(env,2);



}

int main(int argc,char * argv[]) {

	int i=f1();
	i=f2();
	return 0;



}
