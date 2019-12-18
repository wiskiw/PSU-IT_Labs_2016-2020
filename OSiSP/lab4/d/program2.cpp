#include <stdio.h>
#include < dlfcn.h >

int main()
{
void *handle = dlopen("libdynamic.so",RTLD_LAZY);
int(*fun)(void) = dlsym(handle,"hello");
int x = (*fun)();
dlclose(handle);
printf("Return code: %dn",x);
return 0;
};
