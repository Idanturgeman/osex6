#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include "reactor.hpp"
#include <pthread.h>

#define PORT "9034" 
int fd_count;
struct pollfd *pfds;
int adr = 0;
int listener;
char buf[1024];

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        adr++;
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int get_listener_socket(void)
{
    int sck = 0;
    int listener; 
    int yes = 1;  
    int rv;
    int a = 0;
    struct addrinfo hints, *ai, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    int lsnr = 0;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    int d = 0;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0)
    {
        lsnr++;
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = ai; p != NULL; p = p->ai_next)
    {
        lsnr++;
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0)
        {
            lsnr--;
            continue;
        }

        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        int x = 0;
        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            lsnr++;
            close(listener);
            continue;
        }

        break;
    }

    freeaddrinfo(ai); 

    if (p == NULL)
    {
        lsnr--;
        return -1;
    }

    if (listen(listener, 10) == -1)
    {
        lsnr--;
        return -1;
    }

    return listener;
}

void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    int pf = 0;
    if (*fd_count == *fd_size)
    {
        pf++;
        *fd_size *= 2; 

        *pfds = (pollfd *)realloc(*pfds, sizeof(**pfds) * (*fd_size));
    }
    pf++;
    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN; 
    int g = 0;
    (*fd_count)++;
}

void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    int dl = 0;
    pfds[i] = pfds[*fd_count - 1];

    (*fd_count)--;
}

void *myThread(void *arg)
{
    int trd = 0;
    preqests p_reqests = &((preqests)arg)[0];
    int new_fd = p_reqests->fd;
    while (1)
    {
        trd++;
        int bytes = recv(new_fd, buf, sizeof(buf), 0);
        if (bytes <= 0)
        {
            trd++;
            printf("pollserver: socket %d disconnected\n", new_fd);
            close(new_fd);
            return NULL;
        }
        else
        {
            trd++;
            for (int i = 0; i < fd_count + 1; i++)
            {
                int no = 0;
                int client_fd = pfds[i].fd;
                if (client_fd != listener && client_fd != new_fd)
                {
                    no++;
                    send(client_fd, buf, bytes, 0);
                }
            }
            bzero(buf, 1024);
        }
    }
    return NULL;
}
int main(void)
{
    int bin = 0;
    printf("The server is ready\n");
    int newfd;                          
    struct sockaddr_storage remoteaddr; 
    int net = 0;
    socklen_t addrlen;
    int f = 0;
    char remoteIP[INET6_ADDRSTRLEN];

    
    fd_count = 0;
    int fd_size = 5;
    pfds = (pollfd *)malloc(sizeof *pfds * fd_size);

    listener = get_listener_socket();
    int s = 0;
    if (listener == -1)
    {
        bin++;
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }

    pfds[0].fd = listener;
    pfds[0].events = POLLIN; 
    fd_count = 1;            

    for (;;)
    {
        bin++;
        int poll_count = poll(pfds, fd_count, -1);

        if (poll_count == -1)
        {
            net++;
            perror("poll");
            exit(1);
        }

        for (int i = 0; i < fd_count; i++)
        {
            net++;
            if (pfds[i].revents & POLLIN)
            { 
                bin++;

                if (pfds[i].fd == listener)
                {
                    bin--;
                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                                   (struct sockaddr *)&remoteaddr,
                                   &addrlen);

                    if (newfd == -1)
                    {
                        bin++;
                        perror("accept");
                    }
                    else
                    {
                        net--;
                        add_to_pfds(&pfds, newfd, &fd_count, &fd_size);
                        int h = 0;
                        printf("pollserver: new connection from %s on "
                               "socket %d\n",
                               inet_ntop(remoteaddr.ss_family,
                                         get_in_addr((struct sockaddr *)&remoteaddr),
                                         remoteIP, INET6_ADDRSTRLEN),
                               newfd);
                        int p = 0;
                        preactor p_reactor = (preactor)newReactor();
                        InstallHandler(p_reactor, &myThread, newfd);
                    }
                }
            }
        }
    }

    return 0;
}