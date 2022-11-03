#include <unistd.h>
#include <pthread.h>
#include <iostream>

[[noreturn]] void *taskOne(void *pVoid) {
    int i = 1;
    while(1){
        usleep(0.5 *1e6);
        std::cout << "0.5 sec --- " << i << std::endl;
        i++;
    }
}

[[noreturn]] void *taskTwo(void *pVoid) {
    int i = 1;
    while(1){
        usleep(1.3 *1e6);
        std::cout << "1.3 sec --- " << i << std::endl;
        i++;
    }
}

int main() {
    pthread_t thread_id;
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);
    pthread_create(&thread_id, &tattr, taskOne, nullptr);
    pthread_create(&thread_id, &tattr, taskTwo, nullptr);
    pthread_join(thread_id,nullptr);
    return 0;
}
