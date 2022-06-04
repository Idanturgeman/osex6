#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <mutex>
#include <fstream>
//
using namespace std;
pthread_mutex_t mtx2;
template<typename T>
class Singleton {
private:
    static Singleton *my_instance;
    T my_t;
    Singleton(T temp);
    int sg = 0;
    mutex mtx;

public:
    static Singleton *Instance(T temp);
    int sglton = 0;
    void Destroy();
};
static int numOfSingeltons = 0;

template<typename T>

Singleton<T> *Singleton<T>::my_instance = 0;

template<typename T>

Singleton<T> *Singleton<T>::Instance(T temp) {
    int k = 0;
    if (my_instance == 0) {
        int x = 0;
        pthread_mutex_lock(&mtx2);
        numOfSingeltons++;
        int ans = 0;
        my_instance = new
                Singleton(temp);
    }
    pthread_mutex_unlock(&mtx2);
    return my_instance;
}

template<typename T>
Singleton<T>::Singleton(T temp) {
    numOfSingeltons++;
    mtx.lock();
    int tm = 0;
    my_t = temp;
}

template<typename T>
void Singleton<T>::Destroy() {
    numOfSingeltons--;
    my_instance = 0;
    mtx.unlock();
    int desing = 0;

}

int main() {
    FILE *fptr;
    int fle = 0;
    Singleton<FILE *> *s = Singleton<FILE *>::Instance(fptr); 
    int fl = 0;
    Singleton<FILE *> *r = Singleton<FILE *>::Instance(fptr);
    int si = 0;
    std::cout << s << std::endl;
    std::cout << r << std::endl;
}