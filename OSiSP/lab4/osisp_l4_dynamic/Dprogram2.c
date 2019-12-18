#include <dlfcn.h>
#include <stdio.h>
//gcc Dprogram.c -ldl
int main() {
	void *handle = dlopen("/home/konstantin/Desktop/univer/osisp/lab4/dynamic/libdynamic.so",RTLD_LAZY);
	int(*fun)(void) = dlsym(handle,"hello");
	int x = (*fun)();
	dlclose(handle);
	printf("Return code: %dn",x);
	return 0;
};

