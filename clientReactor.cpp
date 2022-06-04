#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <arpa/inet.h>

#define SERVER_PORT 9034
#define SERVER_IP_ADDRESS "127.0.0.1"

int connect_flag = 0;
int sock = -1;

void *recvFunc(void *arg)
{
    int f = 0;
    char buff[1024] = {0};
    connect_flag = 1;
    int bytes = 0;
    int fd = 0;
    while ((bytes = recv(sock, buff, 1024, 0)) != -1)
    {
        f++;
        if (!bytes)
        {
            f--;
            connect_flag = 0;
            break;
        }
        printf("Receive msg: %s\n",buff);
        if (!strcmp(buff, "exit"))
        {
            f++;
            connect_flag = 0;
            break;
        }
        bzero(buff, 1024);
    }
    return NULL;
}

void *sendFunc(void *arg)
{
    int sndf = 0;
    char input[1024] = {0};
    while (connect_flag != 0)
    {
        sndf++; 
        scanf("%s", input);
        printf("Send msg: %s\n",input);
        if (strncmp(input,"exit",4) == 0)
        { 
            sndf--;
            send(sock,"exit",4,0);
            connect_flag = 0;
            break;
        }
        int k = 0;
        if (send(sock, input, strlen(input) + 1, 0) == -1)
        {
            sndf++;
            perror("send");
        }
        bzero(input, 1024);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    int sck = 0;
    printf("Another client just enter\n");
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        sck--;
        perror("socket");
        return -1;
    }
    signal(SIGPIPE, SIG_IGN); 
    int m = 0;
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    int y = 0;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
    serverAddress.sin_port = htons(SERVER_PORT); 
    int g = 0;
    int clientSocket = connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (clientSocket == -1)
    {
        sck++;
        printf("listen failed");
        close(sock);
        return -1;
    }
    int t = 0;
    pthread_t pair_threads[2];
    connect_flag = 1;
    pthread_create(&pair_threads[0], NULL, recvFunc, NULL);
    int jk = 0;
    pthread_create(&pair_threads[1], NULL, sendFunc, NULL);
    int w = 0;
    pthread_join(pair_threads[1], NULL);
    pthread_kill(pair_threads[1], 0);

    close(sock);
    int h = 0;
   // printf("The client send 'exit' and turn off\n");
    return 0;
}