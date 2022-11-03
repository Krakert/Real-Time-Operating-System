#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024

[[noreturn]] void *receiver(void *pVoid) {
    mqd_t mq;
    ssize_t bytes_read;
    struct mq_attr attr{};
    char buffer[MAX_SIZE + 1];

    // Initialize the queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // Create the message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY | O_NONBLOCK, 0644, &attr);

    while (true) {
        // Locate some memory
        memset(buffer, 0x00, sizeof(buffer));
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, nullptr);
        if (bytes_read >= 0) {
            printf("THREAD 2: Received message: %s\n", buffer);
        } else {
            printf("THREAD 2: None \n");
        }
        // Flush STREAM
        fflush(stdout);
        usleep(0.1 * 1e6);
    }
}


void *sender(void *pVoid) {

    mqd_t mq;
    char buffer[MAX_SIZE];

    // Open the queue
    mq = mq_open(QUEUE_NAME, O_WRONLY);

    for (int i = 0; i < 50; ++i) {
        snprintf(buffer, sizeof(buffer), "message %d", i);

        printf("THREAD 1: Send integer: %d\n", i);
        mq_send(mq, buffer, MAX_SIZE, 0);

        fflush(stdout);
    }

    mq_close(mq);
    return nullptr;
}

int main() {

    pthread_t thread_1, thread_2;
    pthread_attr_t tattr;

    //tattr init met defaultwaarden
    pthread_attr_init(&tattr);

    //sched policy Round Robin
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    // Create threads 1 and 2
    pthread_create(&thread_2, &tattr, &receiver, nullptr);
    pthread_create(&thread_1, &tattr, &sender, nullptr);

    // Join threads 1 and 2
    pthread_join(thread_2, nullptr);
    pthread_join(thread_1, nullptr);

    return 0;
}