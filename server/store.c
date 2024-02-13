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
    fclose(fptr);
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
    char * s ="";
    fprintf(fptr, "%s",s);
    fclose(fptr);
    return 0;
}
char * get(){
    FILE* fptr;
 
    // opening the file in read mode
    fptr = fopen("msg", "r");
 
    // checking if the file is opened successfully
    if (fptr == NULL) {
        printf("The file is not opened. The program will now exit.");
        return "";
    }
    char * s = malloc(sizeof(char) * 1024);
    fscanf(fptr, "%s", s);
    fclose(fptr);
    return s;
}