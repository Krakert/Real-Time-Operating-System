#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>

pthread_mutex_t mutex;

void *taskOne(void *pVoid) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 5; ++i) {
        std::cout << "section 1" << std::endl;
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

void * taskTwo(void *pVoid) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 5; ++i) {
        std::cout << "section 2" << std::endl;
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);
    return nullptr;
}


int main() {

    pthread_t thread_1, thread_2;
    pthread_attr_t tattr;

    pthread_mutex_init(&mutex,nullptr);

    pthread_attr_init(&tattr);
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    pthread_create(&thread_1, &tattr, &taskOne, nullptr);
    pthread_create(&thread_2, &tattr, &taskTwo, nullptr);

    pthread_join(thread_1, nullptr);
    pthread_join(thread_2, nullptr);

    return 0;
}