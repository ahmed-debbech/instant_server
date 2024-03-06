#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int sanitizer(int r, char ** a){
    if(r == 1){
        return 0;
    }
    if(strcmp(a[1], "-i") == 0){
        return 1;
    }
}

void set_ip(char * ip){
    FILE * file;
    file = fopen("s_ip", "w");
    fprintf(file, "%s" ,ip);
    fclose(file);
}
char * read_msg(){
    FILE * file;
    file = fopen("/tmp/ms_bu", "r");
    if(file == NULL){
        return NULL;        
    }
    //read it
    char *c = malloc(sizeof(char) * 512);
    fscanf(file, "%s", c);
    fclose(file);
    return c;
}

void send_srv(char * t){
    FILE * file;
    file = fopen("/tmp/ms_bu", "w");
    fprintf(file, "%s" ,t);
    fclose(file);
}

int main(int argc, char **argv){
    int mode = sanitizer(argc, argv);
    char * reply = malloc(sizeof(char) * 512);
    switch (mode){
        case 0:
            char *s = read_msg();
            if(s == NULL) {
                printf("no msg yet!\n");
            }else{
                printf("Reply to: => ");
                printf("%s\n", s);
                scanf("%s", reply);
                send_srv(reply);
                system("clear");
            }
            free(s);
            break;
        case 1:
            set_ip(argv[2]);
            break;;
    }
    free(reply);
    return 0;
}