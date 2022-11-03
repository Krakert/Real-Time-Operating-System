#include <pthread.h>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>


int pipefds[2];

[[noreturn]] void *receiver(void *pVoid) {
    while(1){
        int i, result;
        result = read (pipefds[0],&i,1);
        if (result != 1) {
            perror("read");
            exit(3);
        }
        std::cout << "Thread 2 read: " << i << std::endl;
        sleep(1);
    }
}


void *sender(void *pVoid) {
    int result;
    for (int i = 0; i < 50; ++i) {
        result = write (pipefds[1], &i,1);
        if (result != 1){
            perror ("write");
            exit (2);
        }
        std::cout << "Thread 1 send: " << i << std::endl;
        sleep(1);
    }
    return nullptr;
}


int main() {

    pthread_t thread_1, thread_2;
    pthread_attr_t tattr;

    // Create a one-way communication channel (pipe)
    pipe(pipefds);

    // Init thread attribute *ATTR with default attributes
    pthread_attr_init(&tattr);

    //sched policy Round Robin
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    // Create threads 1 and 2
    pthread_create(&thread_1, &tattr, &sender, nullptr);
    pthread_create(&thread_2, &tattr, &receiver, nullptr);

    // Join threads 1 and 2
    pthread_join(thread_1, nullptr);
    pthread_join(thread_2, nullptr);

    return 0;
}