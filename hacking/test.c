#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int x(unsigned int i, char * c) {

	char a[35];
	unsigned int x1=i;
	strcpy(a,c);
	return x1;
}
int main(int argc, char * argv[]) {
	unsigned int m=222 ;
	unsigned int n;

	n=x(m,argv[1]);
	exit(0);

}

