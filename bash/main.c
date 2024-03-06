#include <stdlib.h>
#include <stdio.h>


void sanitizer(int r, char ** a){
    if(r == 2){

    }
    if(r==3){
        char * ip = a[2];
        printf("ipp: %s\n",ip);
    }
}

int main(int argc, char **argv){
    sanitizer(argc, argv);

    
    return 0;
}