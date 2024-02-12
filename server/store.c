#include "store.h"

int store(char * s){
    FILE* fptr;
 
    // opening the file in read mode
    fptr = fopen("msg", "w");
 
    // checking if the file is opened successfully
    if (fptr == NULL) {
        printf("The file is not opened. The program will now exit.");
        return -1;
    }
    fprintf(fptr, "%s", s);
    return 0;
}
int delete(){
    FILE* fptr;
 
    // opening the file in read mode
    fptr = fopen("msg", "w");
 
    // checking if the file is opened successfully
    if (fptr == NULL) {
        printf("The file is not opened. The program will now exit.");
        return -1;
    }
    return 0;
}
char * get(){
    FILE* fptr;
 
    // opening the file in read mode
    fptr = fopen("msg", "r");
 
    // checking if the file is opened successfully
    if (fptr == NULL) {
        printf("The file is not opened. The program will now exit.");
        return NULL;
    }
    char * s;
    fscanf(fptr, "%s", s);
    return 0;
}