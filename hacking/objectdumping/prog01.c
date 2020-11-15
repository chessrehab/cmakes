#include <stdio.h>
#include <string.h>

int main() {
	char *ptr1;
	char strg[20];
	for (int i=0; i<10;i++) {
		puts("Hello world");
	}
	strcpy(strg,"\n\nwhatuuuuuup!\n");
	printf("%s",strg);
	ptr1=(char*) &strg[5];
	strcpy(ptr1,"    whazzzuuuup!\n");
	printf("%s",strg);
	return 0;
}


