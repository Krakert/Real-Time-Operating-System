#include <cstdio>
#include <pthread.h>
#include <cstdlib>
#include <sched.h>
#include <ctime>

[[noreturn]] void *taskOne(void *pVoid) {
    int m, n;
    while (true) {
        printf("task 1 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
}

[[noreturn]] void *taskTwo(void *pVoid) {
    int m, n;
    while (true) {
        printf("task 2 \n");
        for (m = 0; m <= 1000; m++) {
            for (n = 0; n <= 10000; n++) {

            }
        }
    }
}

[[noreturn]] void *taskThree(void *pVoid) {
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

[[noreturn]] void *taskFour(void *pVoid) {
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
    // Run tasks on core #0
    cpu_set_t mask;
    CPU_ZERO (&mask);
    CPU_SET (0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);

    pthread_attr_t tattr, tattr_1;

    // Init thread attribute *ATTR with default attributes
    pthread_attr_init(&tattr);
    //sched policy Round Robin
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);


    struct sched_param param1;

    // Init thread attribute *ATTR with default attributes
    pthread_attr_init (&tattr_1);
    pthread_attr_setschedpolicy (&tattr_1, SCHED_RR);
    pthread_attr_getschedparam (&tattr_1, &param1);

    param1.sched_priority = 150;

    pthread_attr_setinheritsched (&tattr_1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedparam (&tattr_1, &param1);

    // Create threads 1-4
    pthread_t thread1, thread2, thread3, thread4;
    pthread_create(&thread1, &tattr, taskOne, nullptr);
    pthread_create(&thread2, &tattr, taskTwo, nullptr);
    pthread_create(&thread3, &tattr, taskThree, nullptr);
    pthread_create(&thread4, &tattr, taskFour, nullptr);


    // Join threads 1 and 2
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    return 0;
}
