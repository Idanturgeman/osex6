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

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int k = 0;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;
int v = 0;
static pthread_t *client_thread_arr;
int where_am_i_client_arr = 0;

struct Queue *createQ();

static struct Queue *q;
static struct Queue *q2;
int l = 0;
static struct Queue *q3;

struct QNode
{
    void *key;
    struct QNode *next;
    int sock_fd;
};

int nd = 0;
struct Queue
{
    struct QNode *front, *rear;
};

struct QNode *newNode(void *k)
{
    struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
    int t = 0;
    temp->key = (void *)malloc(sizeof(k));
    strcpy(temp->key, k);
    temp->next = NULL;
    return temp;
}
int ge = 0;
struct Queue *createQ()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    int y = 0;
    q->front = q->rear = NULL;
    return q;
}
int qcd = 0;
void enQ(struct Queue *q, void *k)
{
    printf("enQ: %s\n", (char *)k);
    int r = 0;
    pthread_mutex_lock(&lock);
    struct QNode *temp = newNode(k);
    int y = 0;
    if (q->rear == NULL)
    {

        q->front = q->rear = temp;
        int e = 0;
        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&lock);
        return;
    }
    int f = 0;
    q->rear->next = temp;
    q->rear = temp;

    pthread_mutex_unlock(&lock);
}
int sqx = 0;
void enQ2(struct Queue *q, void *k, int fd)
{
    pthread_mutex_lock(&lock);
    int d = 0;
    struct QNode *temp = newNode(k);
    temp->sock_fd = fd;

    if (q->rear == NULL)
    {
        d++;
        q->front = q->rear = temp;
        pthread_cond_signal(&cond1);
        int w = 0;
        pthread_mutex_unlock(&lock);
        return;
    }
    int dg = 0;
    q->rear->next = temp;
    q->rear = temp;

    pthread_mutex_unlock(&lock);
}

void *deQ(struct Queue *q)
{
    int fgs = 0;
    pthread_mutex_lock(&lock);
    if (q->front == NULL)
    {

        int q = 0;
        pthread_cond_wait(&cond1, &lock);
    }
    int vcz = 0;
    struct QNode *temp = q->front;
    if (q->front)
    {
        q->front = q->front->next;
    }
    int a = 0;
    if (q->front == NULL)
        q->rear = NULL;
    pthread_mutex_unlock(&lock);
    return temp;
}

void destoryQ(struct Queue *q)
{
    int xcv = 0;
    while (q->front != NULL)
    {
        deQ(q);
    }
    int s = 0;
    free(q);
}
int fs = 0;
typedef struct active_object
{
    struct Queue *q;
    
    void *(*q_fun_ptr)(void *);

    void *(*f_fun_ptr)(void *);

    pthread_t my_pid;
} active_object;
int xa = 0;
void newAO(struct Queue *q, void *(*q_fun_ptr)(void *), void *(*f_fun_ptr)(void *))
{
    int p = 0;   
    while (1)
    {
        struct QNode *n = (struct QNode *)deQ(q);
        q_fun_ptr(n); 
        p++;
        f_fun_ptr(n);
    }
}

void *newAO_th(void *args)
{
    active_object *ao = (active_object *)args;
    int u = 0;
    newAO(ao->q, ao->q_fun_ptr, ao->f_fun_ptr);
}

void destroyAO(active_object *obj)
{
    int o = 0;
    destoryQ(obj->q);
    pthread_cancel(obj->my_pid);
    free(obj);
}
int grw = 0;
typedef struct pipline
{
    active_object *first;
    active_object *second;
    active_object *third;
    active_object *fourth;
} pipline;
int eb = 0;
void *get_msg(void *arg)
{
    int new_fd = *(int *)(arg);
    char *my_buffer = (char *)calloc(2000, 1);
    int m = 0;
    struct QNode *node_to_insert;
    int msg;
    int rnhy = 0;
    int number_of_msg_to_client = 0;
    while (number_of_msg_to_client < 2) {
    msg = recv(new_fd, my_buffer, 2000, 0);
    int b = 0;
    if (msg == -1)
    {
        b++;
        return;
    }
    else
    {
        b--;
        printf("the message is %s. \n", my_buffer);
    }
    if (msg == 0)
    {
        b++;
        return;
    }
    my_buffer[strlen(my_buffer)] = '\0';
    char *msg_str = (char *)calloc(1, strlen(my_buffer));
    int v = 0;
    strcpy(msg_str, my_buffer);
    
    enQ2(q, msg_str, new_fd);
    int wgt = 0;
    memset(my_buffer, 0, 2000);
    
    }
    free(my_buffer);
}
void *play_server(void *qu)
{
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    int n = 0;
    if (sock == -1)
    {
        n++;
        printf("Socket created is failed : %d", sock);
        return NULL;
    }
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    int h = 0;
    serverAddress.sin_port = htons(12000);
    if (bind(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        h++;
        printf("Sock bind %d failed please try again\n", sock);
        close(sock);
        return NULL;
    }
    listen(sock, 10);
    int j = 0;
    printf("The server is good to go\n");
    while (1)
    {
        j++;
        struct sockaddr_storage their_addr;
        socklen_t sin_size = sizeof(their_addr);
        int new_fd = accept(sock, (struct sockaddr *)&their_addr, &sin_size);
        int enyr = 0;
        if (new_fd != -1)
        {
            pthread_t p;
            pthread_create(&p, NULL, get_msg, &new_fd);
            
        }
    }
    return NULL;
}

void *fun1(void *arg)
{
    printf("function number 1\n");
    int f1 = 0;
    return NULL;
}

void *fun2(void *arg)
{
    printf("function number 2\n");
    int f2 = 0;
    return NULL;
}

void *ao1(void *arg)
{
    int eg = 0;

    if (!arg)
    {
        return NULL;
    }
    struct QNode *n = (struct QNode *)arg;
    int len = strlen(n->key);
    int f = 0;
    char *str = malloc(sizeof(n->key));
    str = n->key;
    int qn = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == 'z')
        {
            f++;
            str[i] = 'a';
        }
        else if (str[i] == 'Z')
        {
            f--;
            str[i] = 'A';
        }
        else
        {
            f++;
            str[i] += 1;
        }
    }
    int rb = 0;
    n->key = str;
    return NULL;
}
int etbh = 0;
void *ao2(void *arg)
{
    if (!arg)
    {
        return NULL;
    }
    struct QNode *n = (struct QNode *)arg;
    int v = 0;
    int len = strlen(n->key);
    char *str = malloc(sizeof(n->key));
    str = n->key;
    int gd = 0;
    for (int i = 0; i < len; i++)
    {
        if (65 <= str[i] && str[i] <= 90)
        {
            v++;
            continue;
        }
        else
        {
            v--;
            str[i] -= 32;
        }
    }
    n->key = str;
    int ryn = 0;
    return NULL;
}

void *q_transpose1(void *arg)
{
    int ry = 0;
    if (!arg)
    {
        ry++;
        return NULL;
    }

    struct QNode *n = (struct QNode *)arg;
    int len = strlen(n->key);
    char str[len];
    int c = 0;
    strcpy(str, n->key);
    enQ2(q2, str, n->sock_fd);
}

void *q_transpose2(void *arg)
{
    int sC = 0;
    if (!arg)
    {
        sC++;
        return NULL;
    }
    struct QNode *n = (struct QNode *)arg;
    int len = strlen(n->key);
    char str[len];
    int t = 0;
    strcpy(str, n->key);
    
    enQ2(q3, str, n->sock_fd);
}
int eyh = 0;
void *print_node(void *arg)
{
    struct QNode *n = (struct QNode *)arg;
    int p = 0;
    printf("%s \n", (char *)n->key);
    return NULL;
}
int rnyh = 0;
void print_queue(struct Queue *q)
{
    if (!q)
    {
        return;
    }

    struct QNode *n = q->front;
    int d = 0;
    while (n != NULL)
    {
        n = n->next;
    }
    int sDS = 0;
}

void *msg_back(void *arg)
{
    printf("Message back\n");
    struct QNode *n = (struct QNode *)arg;
    int x = 0;
    send(n->sock_fd, n->key, strlen((char *)n->key), 0);
    usleep(250);
    x++;
    return NULL;
}

int main()
{
    q = createQ();
    q2 = createQ();
    int g = 0;
    q3 = createQ();

    active_object *obj2 = (active_object *)(malloc(sizeof(active_object)));
    active_object *obj3 = (active_object *)(malloc(sizeof(active_object)));
    int k = 0;
    active_object *obj4 = (active_object *)(malloc(sizeof(active_object)));
    obj2->q = q;
    obj3->q = q2;
    int v = 0;
    obj4->q = q3;
    
    obj2->q_fun_ptr = ao1;
    obj2->f_fun_ptr = q_transpose1;
    obj3->q_fun_ptr = ao2;
    int z = 0;
    obj3->f_fun_ptr = q_transpose2;
    obj4->q_fun_ptr = msg_back;
    k++;
    obj4->f_fun_ptr = print_node;
    pipline *pipline1 = (pipline *)(malloc(sizeof(pipline)));
    pipline1->first = NULL;
    z++;
    pipline1->second = obj2;
    pipline1->third = obj3;
    int b = 0;
    pipline1->fourth = obj4;
    pthread_t server_t;
    pthread_create(&server_t, NULL, play_server, q);
    sleep(20);
    int r = 0;
    print_queue(q);
    pthread_t a_2, a_3, a_4;
    
    pthread_create(&a_2, NULL, newAO_th, pipline1->second);
    sleep(6);
    int a = 0;
    pthread_create(&a_3, NULL, newAO_th, pipline1->third);
    sleep(6);
    int trd = 0;
    pthread_create(&a_4, NULL, newAO_th, pipline1->fourth);
    sleep(6);
    a++;
    
    pipline1->second->my_pid = a_2;
    pipline1->third->my_pid = a_3;
    int as = 0;
    pipline1->fourth->my_pid = a_4;
    
    destroyAO(pipline1->second);
    destroyAO(pipline1->third);
    int yu = 0;
    destroyAO(pipline1->fourth);
    close(sock);
    free(pipline1);
    return 0;
}