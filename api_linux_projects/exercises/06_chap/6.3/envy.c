//implementation of setenv() and unsetenv() using putenv() and getenv()





#include <stdlib.h>
#include <string.h>
//strcat covered in string.h
#include <stdio.h>
//printf covered in stdio.h
extern int putenv(char *string); //string is allocated by program and is of 'name=value' format
extern char *getenv(const char* name); //returns a pointer to the value in the environment on the stack



//extern int setenv(const char *name, const char *value, int overwrite);
//extern int unsetenv(const char *name);


extern char **environ;

int setenv0(const char *name,const char *value, int overwrite) {

	char **en;
	int nr_chars;
	char *ptr;
	if (getenv(name)==NULL) {
		nr_chars=strlen(name)+strlen(value)+1;
		ptr=malloc(nr_chars+1);
		strcpy(ptr,name);
		strcat(ptr,"=");
		strcat(ptr,value);
		int i=putenv(ptr);
	} else {

		for (en=environ;*en!=NULL;en++){
			if(strncmp(name,*en,strlen(name))==0) {
				nr_chars=strlen(name)+strlen(value)+1;
				ptr=malloc(nr_chars+1);
				strcpy(ptr,name);
				strcat(ptr,"=");
				strcat(ptr,value);
				*en=ptr;
			} 
		}
	}


}
int unsetenv0(const char *name) {
	char **en,**en2;

	for(en=environ;*en!=NULL;en++) {
		if(strncmp(*en,name,strlen(name))==0) {
			for(en2=en;*en2!=NULL;en2++) 	*en2=*(en2+1);
			en--;
		}
	}
	return 0;

}

int main(int argc, char *argv[]) {
	char *name="martin";
	char *var="svec";
	char *var2="sveky";
	setenv0(name,var,1);
	setenv0(name,var2,1);
	printf("\n fetching variable %s: result is: %s\n", name,getenv(name));
	unsetenv0(name);
	printf("\n fetching variable %s: result is: %s\n", name,getenv(name));

}
