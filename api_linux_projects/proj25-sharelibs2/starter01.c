#include "header01.h"
#include "tlpi_hdr.h"
#include <dlfcn.h>

int main(int argc, char *argv[]) {
	
	void *libHandle;
	int (*fmod01)(void);
	int (*fmod03)(void);
	void *var;

	printf("\nstarting....\n");


	libHandle=dlopen("lib/libmmm.so",RTLD_LAZY);
	(void) dlerror();
	*(void **) (&fmod01)=dlsym(libHandle,"module01_speaks");
//	err=dlerror();
	(*fmod01)();
	*(void **) (&fmod03)=dlsym(libHandle,"module03_speaks");
	(*fmod03)();
	var=dlsym(libHandle,"test_var");
	printf("\npremenna:%d\n",*((int*) var));		
	printf("\nshutting down...");
	return 0;	
}
