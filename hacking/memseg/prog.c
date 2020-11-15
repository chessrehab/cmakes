#include <stdio.h>
#include <stdlib.h>

int glb_int1,glb_int2,glb_int3;
int glb_int_init=13;


int func1(int arg1,char* arg2) {
	printf("in func1-%s\n",arg2);
	return 1;
}
int func2(int arg1,int arg2) {
	printf("in func2\n");
	return 2;
}
int func3(int a,double x) {
	int f3=func2(a,(int) x);
	printf("in funct3\n");
}
int main(int argc, char *argv[]) {
	printf("address of glb_int1 is %p\n",&glb_int1);
	printf("address of glb_int2 is %p\n",&glb_int2);
	printf("address of glb_int3 is %p\n",&glb_int3);

	printf("address of glb_int_init  is %p\n",&glb_int_init);
	glb_int1=11;
	glb_int2=12;
	glb_int3=13;

	int m1,m2;
	m1=func1(16436922,"mainfunc1");
	m2=func2(16436922,16436922);
	return 0;

}

