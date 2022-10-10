#include <iostream>
#include <pthread.h>

void * taskOne(void *pVoid) {
    int m, n;
    while (1) {
        printf("task 1 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
}

void * taskTwo(void *pVoid) {
    int m, n;
    while (1) {
        printf("task 2 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
}

void * taskThree(void *pVoid) {
    int m, n;
    while (1) {
        printf("task 3 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
}

void * taskFour(void *pVoid) {
    int m, n;
    while (1) {
        printf("task 4 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
}


int main() {
    pthread_attr_t tattr;
    pthread_t thread1, thread2, thread3, thread4;
    pthread_attr_init(&tattr);                                  //tattr init met defaultwaarden
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);        //sched policy aanpassen
    pthread_create (&thread1, &tattr, taskOne, nullptr);
    pthread_create (&thread2, &tattr, taskTwo, nullptr);
    pthread_create (&thread3, &tattr, taskThree, nullptr);
    pthread_create (&thread4, &tattr, taskFour, nullptr);


    // Join threads
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
    pthread_join(thread3, nullptr);
    pthread_join(thread4, nullptr);

    return 0;
}
