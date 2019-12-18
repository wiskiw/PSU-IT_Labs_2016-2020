#include <stdio.h>
#include <dlfcn.h>

int main(){
void *handle = dlopen("/home/wiskiw/SSDStorage/UNI/LVL2/PART2/OSiSP/lab4/d/libdynamic2.so",RTLD_LAZY);
int(*fun)(void) = dlsym(handle,"hello");
int x = (*fun)();
dlclose(handle);
printf("Return code: %dn",x);
return 0;
};
