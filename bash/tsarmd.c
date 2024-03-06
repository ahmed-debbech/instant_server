#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <curl/curl.h>

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
char * get_ip(){
    FILE * file;
    file = fopen("s_ip", "r");
    if(file == NULL){
        return NULL;
    }
    char * c = malloc(sizeof(char) * 128);
    fscanf(file, "%s" ,c);
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

    int PORT = 9880;

    CURL *curl = curl_easy_init();
    CURLcode res;
    char * response;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (char *)response);
        res = curl_easy_perform(curl);

        /* check for errors */ 
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
        printf("mememem\n");
        printf("chunk %s\n", response);
    }


    return 0;
}