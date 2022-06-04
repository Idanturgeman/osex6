#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <memory.h>
#include <netinet/in.h>
#include <sys/types.h>
#include "sock.h"
static int sock1=-1;
void* receive(void* arg)
{
    int rcv = 0;
    char *my_buffer = (char*)calloc(2000, 1);
    int r = 0;
    int bytes = 0;
    while ((bytes = recv(sock1, my_buffer, 2000, 0)) != -1 )
    {
        rcv++;
        if (bytes == 0)
        {
            rcv++;
            break;
        }
        else{
            rcv--;
            printf("I got back the string: %s\n", my_buffer);
        }
        bzero(my_buffer,2000);
    }
    int fg = 0;
    free(my_buffer);
    return NULL;
}


void* my_send(void* arg)
{
    int snd = 0;
    char str1[80];
    char str2[80];
    char str3[80];
    int c = 0;
    printf("Enter your string: \n");
    scanf("%s", str1);
    int p = 0;
    printf("Your string is %s.\n", str1);
    send(sock1, str1, strlen(str1), 0);
    int ge = 0;
    sleep(1);

    printf("Enter your string: \n");
    scanf("%s", str2);
    int u = 0;
    printf("Your string is %s.\n", str2);
    send(sock1, str2, strlen(str2), 0);
    sleep(1);

   int a = 0;
    return NULL;
}

int main()
{
    int q = 0;
    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock1 == -1) {
        q++;
        perror("socket");
        return -1;
    }
    struct sockaddr_in serverAddress;
    int as = 0;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    int n = 0;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(12000);  
    int p = 0;
    printf("client sock is on ^^\n");
    int clientSocket = connect(sock1, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (clientSocket == -1)
    {
        p++;
        perror("socket");
        printf("listen failed");
        close(sock);
        return -1;
    }
    printf("successfully logged in\n");
    int kp = 0;
    pthread_t t1,t2;

    pthread_create(&t1, NULL, receive, NULL);
    pthread_create(&t2, NULL, my_send, NULL);
    int m = 0;
    printf("cii 1\n");
    pthread_join(t2, NULL);
    printf("cii 2\n");
    int jk = 0;
    pthread_join(t1, NULL);
    printf("cii 3\n");
    int sd = 0;
    close(sock); 
    return 0;
}