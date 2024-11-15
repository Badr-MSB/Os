#include "ktest.h"

extern int printf(const char *, ...);

char src[] = "deadbeaf deadbea  a ";
char dst[21] = {0};

void kmemncpy_test(){
    kmemncpy(src,dst,21);
    for(int i = 0; i<21; i++){
        if(src[i] != dst[i]){
            printf("there is an error in memcpy\n");
            return;
        }
    }
    printf("memcpy seems correct\n");
    return;
}