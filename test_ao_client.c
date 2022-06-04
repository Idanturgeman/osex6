
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
#include <time.h>
#include <stdlib.h>

static int sock1 = -1;

void *receive(void *arg) {
    int rec = 0;
    char *my_buffer = (char *) calloc(2000, 1);

    int bytes = 0;
    while ((bytes = recv(sock1, my_buffer, 2000, 0)) != -1) {
        if (bytes == 0) {
            rec++;
            break;
        } else {
            rec--;
            printf("String back: %s\n", my_buffer);
        }
        rec++;
        bzero(my_buffer,2000);
    }
    rec++;
    free(my_buffer);
    return NULL;
}


void *my_send(void *arg) {
    int snd = 0;
    char *a = "Idan";
    char *b = "Turgeman";
    char *c = "MadonA";
    int ch1 = 0;
    char *d = "GeFen";
    char *e = "levI";
    char *f = "Pamela";
    int ch2 = 0;
    char *g = "tushTush";
    char *h = "bumbUm";
    char *i = "Loklok";
    int temp = 0;
    for (int j=0; j<2; j++){
        snd++;
        srand(time(NULL));
        int r = rand()%8;
        if (r==0){
            temp++;
            printf("send: %s \n", a);
            send(sock1, a, strlen(a), 0);
            sleep(1);
        }
        if (r==1){
            temp++;
            printf("send: %s \n", b);
            send(sock1, b, strlen(b), 0);
            sleep(1);
        }
        if (r==2){
            temp++;
            printf("send: %s \n", c);
            send(sock1, c, strlen(c), 0);
            sleep(1);
        }
        if (r==3){
            temp++;
            printf("send: %s \n", d);
            send(sock1, d, strlen(d), 0);
            sleep(1);
        }
        if (r==4){
            temp++;
            printf("send: %s \n", e);
            send(sock1, e, strlen(e), 0);
            sleep(1);
        }
        if (r==5){
            temp++;
            printf("send: %s \n", f);
            send(sock1, f, strlen(f), 0);
            sleep(1);
        }
        if (r==6){
            temp++;
            printf("send: %s \n", g);
            send(sock1, g, strlen(g), 0);
            sleep(1);
        }
        if (r==7){
            temp++;
            printf("send: %s \n", h);
            send(sock1, h, strlen(h), 0);
            sleep(1);
        }
        if (r==8){
            temp++;
            printf("send: %s \n", i);
            send(sock1, i, strlen(i), 0);
            sleep(1);
        }
    }
    return NULL;
}

int main() {
    int sck = 0; 
    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock1 == -1) {
        sck++;
        perror("socket");
        return -1;
    }
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    int srv = 0;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(12000);  
    int clnt = 0;
    printf("The client is good to go\n");
    int clientSocket = connect(sock1, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (clientSocket == -1) {
        clnt++;
        perror("socket");
        printf("the listen is not succeeded");
        srv++;
        close(sock);
        return -1;
    }

    pthread_t t1, t2;

    pthread_create(&t1, NULL, receive, NULL);
    pthread_create(&t2, NULL, my_send, NULL);
    int trd = 0;
    pthread_join(t2, NULL);
    pthread_join(t1, NULL);

    close(sock); 
    return 0;
}