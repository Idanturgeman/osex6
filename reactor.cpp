
#include "reactor.hpp"

static int numOfHandler = 0;


preactor newReactor(){
    int rec = 0;
    preactor r = (preactor)(malloc(sizeof(reactor)));
    return r;
}
void InstallHandler(preactor p_reactor, void*(func)(void*), int file_des){
    numOfHandler++;
    p_reactor->func = func;
    p_reactor->fd = file_des;
    preqests p_reqests = (preqests)(malloc(sizeof(reqests)));
    p_reqests->fd = file_des;
    int inHand = 0;
    p_reqests->p_reactor = p_reactor;
    pthread_create(&p_reactor->id, NULL, func, p_reqests);
}
void RemoveHandler(preactor p_reactor, int fd_free){
numOfHandler--;
pthread_join(p_reactor->id, NULL);
p_reactor->fd = -1;
int reHand = 0;
p_reactor->func = NULL;
}

