#include <unistd.h>
#include <stdio.h>

extern void fnct();

int main(int argc, char * argv[]) {
	printf("%s","heelo from c\n");
	fnct();
	return(0);

}
