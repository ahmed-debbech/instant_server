#include "server.h"
#include "utils.h"
#include "store.h"

struct HttpReq http_request_parser(char * buff){

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
            request.path = malloc(sizeof(char) * strlen(parts[1]));
            request.protocol = malloc(sizeof(char) * strlen(parts[2]));
            strcpy(request.path, parts[1]);
            strcpy(request.protocol, parts[2]);
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

char * handle(char * buff){
    printf("handle\n");
    struct HttpReq req = http_request_parser(buff);
    //struct HttpRes res = http_response_constructor();

    char * f;
    char * s = malloc(sizeof(char) * 30);
    if(strncmp(req.path, "/seen", 5) == 0){
       delete();
    }
    if(strncmp(req.path, "/", 1) == 0){
        if(strncmp(req.method, "GET", 3) == 0){
            f = get();
        }else{
           store(req.body);
           return
        }
    }

    return NULL;
}

void run_server(int sockfd){
    
    struct Sessions sess;
    sess.length = 0;

    while(1){
        int connfd = accept(sockfd, 0,0); 
        //sess.arr[sess.length] = connfd;
        //sess.length++;

        if (connfd < 0) { 
            printf("server could not accept session with index %d\n", sess.length); 
            return ;
        }

        char buff[MAX_BUFF_CLIENT];
        memset(buff,'\0', sizeof(buff));

        ssize_t read_size = read(connfd, buff, MAX_BUFF_CLIENT);

        char serv_buff[MAX];
        memset(serv_buff,'\0', sizeof(serv_buff));
        char * serv = handle(buff);

        strcpy(serv_buff ,
        "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\n\r\n"
        );
        strcpy(serv_buff ,serv);

        printf("res: [%s]\n", serv_buff);
        send(connfd, serv_buff, strlen(serv_buff), 0);

        free(serv);
        close(connfd);
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
    run_server(sockfd);

    // After chatting close the socket 
    close(sockfd); 
    return 0;
}