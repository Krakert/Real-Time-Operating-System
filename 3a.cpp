#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>

sem_t sem;

[[noreturn]] void *taskOne(void *pVoid) {
    for (int i = 0; i < 5; ++i) {
        std::cout << "section 1" << std::endl;
        sleep(1);
    }
    sem_post(&sem);
    return nullptr;
}

[[noreturn]] void * taskTwo(void *pVoid) {
    sem_wait(&sem);
    for (int i = 0; i < 5; ++i) {
        std::cout << "section 2" << std::endl;
        sleep(1);
    }
    return nullptr;
}


int main() {

    pthread_t thread_1, thread_2;
    pthread_attr_t tattr;

//  Pshared has the value 0, semaphore is shared between the threads of a process.
    sem_init(&sem, 0, 0);

    // Init thread attribute *ATTR with default attributes
    pthread_attr_init(&tattr);

    //sched policy Round Robin
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    // Create threads 1 and 2
    pthread_create(&thread_1, &tattr, &taskOne, nullptr);
    pthread_create(&thread_2, &tattr, &taskTwo, nullptr);

    // Join threads
    pthread_join(thread_1, nullptr);
    pthread_join(thread_2, nullptr);

    return 0;
}