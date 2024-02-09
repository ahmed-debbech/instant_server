

#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
#define MAX_BUFF_CLIENT 500
#define MAX 900
#define PORT 9888
#define NUM_CNX 5
#define SA struct sockaddr 
   
struct Sessions{
    int arr[NUM_CNX];
    int length;
};

struct Header{
    char *key;
    char *value;
};

struct HttpReq{

    char *method;
    char *path;

    struct Header headers[50];
    int len_header;

    char *body;
};

void remove_spaces(char* s) {
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}
char **  get_parts_by_space(char * s){
    char *token;
    char * m;
    strcpy(m, s);
    token = strtok(m, " ");

    size_t i = 1; 
    char ** devids = NULL;
    devids = malloc(sizeof(char **)*i);
    strcpy(devids[0], token);
    ///////////////////////////////////////////////////////////////// STOPEDD HERE
    while( token != NULL ) {
        printf("1\n");
        token = strtok(NULL, " ");
        printf("2\n");
        devids = realloc(devids, sizeof(char *)*i);
        printf("3\n");
        strcpy(devids[0], token);
        printf( "%s\n", devids[i-1]);
        i++;
    }
    return devids;
}

struct HttpReq http_parser(char buff[]){
    struct HttpReq request;

    char *token;
    token = strtok(buff, "\n");
    //first line of raw http request parsing
    if(strncmp("G", token,1) == 0){ //it is a GET req
        strcpy(request.method, "GET");
    }
    if(strncmp("P", token,1) == 0){ // it is a POST req
        strcpy(request.method, "POST");
    }
    get_parts_by_space(token);
    token = strtok(buff, "\n");
    while( token != NULL ) {
        printf( "%s\n", token);
        token = strtok(NULL, "\n");
        
    }
    return request;
}

void handle(char buff[]){
    printf("handle\n");
    http_parser(buff);
}

void start_server(int sockfd){
    
    struct Sessions sess;
    sess.length = 0;

    while(1){
        int connfd = accept(sockfd, 0,0); 
        sess.arr[sess.length] = connfd;
        sess.length++;

        if (connfd < 0) { 
            printf("server could not accept session with index %d\n", sess.length); 
            return ;
        }

        char buff[MAX_BUFF_CLIENT];
        read(connfd, buff, MAX_BUFF_CLIENT); 
        handle(buff);
    }
}

int main(){ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
    
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        return -1;
    }
   
    // assign IP, PORT 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
   
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        return -1; 
    }

    // Now server is ready to listen and verification 
    if ((listen(sockfd, NUM_CNX))  != 0) { 
        printf("Listen failed...\n"); 
        return -1; 
    }

    printf("Server listening on port %d\n", PORT);
    start_server(sockfd);

    // After chatting close the socket 
    close(sockfd); 
    return 0;
}