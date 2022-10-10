#include <iostream>
#include <pthread.h>

void *taskOne(void *pVoid) {
    int m, n;
    while (true) {
        printf("task 1 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
}

void *taskTwo(void *pVoid) {
    int m, n;
    while (true) {
        printf("task 2 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
}

void *taskThree(void *pVoid) {
    int i, m, n;
    for (i = 0; i < 40; i++) {
        printf("task 3 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
    return pVoid;
}

void *taskFour(void *pVoid) {
    int i, m, n;
    for (i = 0; i < 40; i++) {
        printf("task 4 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
    return pVoid;
}


int main() {
    pthread_attr_t tattr;
    pthread_t thread1, thread2, thread3, thread4;

    //tattr init met defaultwaarden
    pthread_attr_init(&tattr);

    //sched policy Round Robin
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    // Create threads 3 and 4
    pthread_create(&thread3, &tattr, taskThree, nullptr);
    pthread_create(&thread4, &tattr, taskFour, nullptr);

    // Join when done
    pthread_join(thread3, nullptr);
    pthread_join(thread4, nullptr);

    // Create threads 1 and 2
    pthread_create(&thread1, &tattr, taskOne, nullptr);
    pthread_create(&thread2, &tattr, taskTwo, nullptr);

    // Join threads 1 and 2
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    return 0;
}
