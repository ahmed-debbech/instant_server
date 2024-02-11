

#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
#define MAX_BUFF_CLIENT 100000
#define MAX 900
//#define PORT 9888
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
struct HttpReq http_parser(char * buff){

    printf("buffer: \n[%s]\n\n", buff);
    struct HttpReq request;

    int size;
    char ** tokens = get_token(buff, '\n', &size);
    int TOP_LINE = 0;
    int BODY_START = size-1;
    int counter = 0;
    request.len_header = 0;
    for(counter = 0; counter <= size-1; counter++){
        
        if(counter == TOP_LINE){ //first line of raw http request parsing
            if(strncmp("G", tokens[counter],1) == 0){ //it is a GET req
                request.method = (char *)malloc(3 * sizeof(char));
                strcpy(request.method, "GET");
            }
            if(strncmp("P", tokens[counter],1) == 0){ // it is a POST req
                request.method = (char *)malloc(4 * sizeof(char));
                strcpy(request.method, "POST");
            }
            int s;
            char ** parts = get_token(tokens[counter], ' ', &s);
            request.path = malloc(sizeof(char) * 50);
            strcpy(request.path, parts[1]);
        }
        if(counter == BODY_START){
            request.body = malloc(sizeof(char) * strlen(tokens[counter]));
            request.body = tokens[counter];
        }
        if((counter != TOP_LINE) && (counter != BODY_START)){ //it is a header
            int s;
            char ** parts = get_token(trimer(tokens[counter]), ':', &s);
            if(s > 1 ){
                request.headers[request.len_header].key = malloc(sizeof(char) * strlen(parts[0]));
                if(s > 2){
                    char * full_value = malloc(sizeof(char));
                    for(int g=1; g<=s-1; g++){
                        full_value = realloc(full_value, sizeof(char) * (strlen(parts[g])+1));
                        strcat(full_value, parts[g]);
                        if(g != s-1) //not the end yet!
                        strcat(full_value, ":");
                    }
                    request.headers[request.len_header].value = malloc(sizeof(char) * strlen(full_value));
                    request.headers[request.len_header].key = parts[0];
                    request.headers[request.len_header].value = full_value;
                }else{ //if it is 2
                    request.headers[request.len_header].value = malloc(sizeof(char) * strlen(parts[1]));
                    request.headers[request.len_header].key = parts[0];
                    request.headers[request.len_header].value = parts[1];
                }
                request.len_header++;
            }
        }
        
    }
    return request;
}

void handle(char * buff){
    printf("handle\n");
    struct HttpReq req = http_parser(buff);
    printf("%s %s %s %s %s %d\n",
    req.path,
    req.method,
    req.headers[5].key,
    req.headers[5].value,
    req.body,
    req.len_header
    );
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
        memset(buff,'\0', sizeof(buff));

        ssize_t read_size = read(connfd, buff, MAX_BUFF_CLIENT); 
        printf("read size: %ld\n", read_size);
        handle(buff);
    }
}
int * get_port(){
    int sockfd;
    struct sockaddr_in servaddr, cli; 
    int PORT = 9879;
    do{
        PORT++;
        // socket create and verification 
        sockfd = socket(AF_INET, SOCK_STREAM, 0); 
        if (sockfd == -1) { 
            printf("socket creation failed...\n"); 
        }
    
        // assign IP, PORT 
        bzero(&servaddr, sizeof(servaddr)); 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
        servaddr.sin_port = htons(PORT); 
    }while((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0);
    int *arr = malloc(sizeof(int) * 2);
    arr[0] = sockfd;
    arr[1] = PORT;
    return arr;
}
int main(){ 
    int sockfd, connfd; 
    int PORT;

    int * d = get_port();
    sockfd = d[0];
    PORT = d[1];

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