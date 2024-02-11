#include "utils.h"


char ** get_token(char * buff, char tok, int * final_size){
    //FILE *fptr;
    //fptr = fopen("a.txt", "w");

    buff[strlen(buff)] = tok;
    int j, y=0;
    int h = 0;
    char **tokens = (char **) malloc(sizeof(char*) * (y+1));
    char * m = malloc(sizeof(char) * (h+1)); 
    for(j=0; j<=strlen(buff)-1; j++){
        if((buff[j] != tok)){
            m[h] = buff[j];
            h++;
            m = realloc(m, sizeof(char) * (h+1));
        }else{
            if(m != NULL){
                h++;
                m = realloc(m, sizeof(char) * (h+1));
                m[h] = '\0';
                tokens[y] = m;
                //printf("D: %s\n", tokens[y]);
                //fprintf(fptr, "%s", m);
                y++;
                tokens = (char **) realloc(tokens, sizeof(char*) * (y+1));
                h = 0;
                m = malloc(sizeof(char) * (h+1));
            }
        }
    }
    //fclose(fptr);
    (*final_size) = (y);
    return tokens;
}
int is_white_char(char c){
    char * white = "\n \r\t";
    for(int i=0;i<=strlen(white)-1; i++){
        if(white[i] == c) return 1;
    }
    return 0;
}
char * trimer(char * s){
    char * x = malloc(sizeof(char) * strlen(s));
    int r=0;
    for(int i=0; i<=strlen(s)-1; i++){
        if(!is_white_char(s[i])){
            x[r] = s[i];
            r++;
        }
    }
    return x;
}