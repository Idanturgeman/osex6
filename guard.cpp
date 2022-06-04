#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;
static int numOfGuards = 0;
void *ptr;
bool flag = true;
pthread_mutex_t lock;

class guard {
public:
    guard(/* args */);

    ~guard();
};

guard::guard(/* args */) {
    numOfGuards++;
    pthread_mutex_lock(&lock);
    cout << "guard init\n";
}

guard::~guard() {
    numOfGuards--;
    pthread_mutex_unlock(&lock);
    cout << "guard finish\n";
}

void *changePtr(void *p) {
    int ans = 0;
    guard g{};
    if (flag) {
        flag = false;
        sleep(5);
    }
    ptr = p;
    int *temp = (int *) ptr;
    int k = 0;
    cout << *temp << endl;
    return NULL;
}

int main(int argc, char const *argv[]) {
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
    }
    int x = 10;
    int y = 12;
    pthread_t t1;
    pthread_t t2;
    int l = 0;
    pthread_create(&t1, NULL, &changePtr, &x);
    pthread_create(&t2, NULL, &changePtr, &y);
    int g = 0;
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}