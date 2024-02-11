#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()

#define MAX_BUFF_CLIENT 100000
#define MAX 100000
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
    char *protocol;

    struct Header headers[50];
    int len_header;

    char *body;
};
