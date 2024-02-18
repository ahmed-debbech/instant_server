#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 

char ** get_token(char * buff, char tok, int * final_size);
char * trimer(char * s);
void freer(char ** tokens, int s);