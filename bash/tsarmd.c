#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <curl/curl.h>

char * big_resp;

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

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    //printf("%s",(char *)contents);
    userp = (char*) malloc(sizeof(char) * 512);
    big_resp = (char*) malloc(sizeof(char) * 512);
    strcpy((char *)userp, (char *)contents);
    strcpy((char *)big_resp, (char *)contents);
    //printf("[%s]\n",(char *)userp);
    return realsize;
}

void make_get(){
    printf("appel\n");

    CURL *curl = curl_easy_init();
    CURLcode res;
    char * response;
    if (curl) {
        const char *url = "http://localhost:9880";
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
}

void store(char * s){
    char * current_msg = read_msg();
    if(strcmp(current_msg, s) != 0){
        printf("difff");
        send_srv(s);
    }
    free(current_msg);
}

int main(int argc, char **argv){

    int PORT = 988;

    while(1){
        make_get();
        store(big_resp);
        sleep(1);
    }

    return 0;
}