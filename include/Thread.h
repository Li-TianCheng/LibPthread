//
// Created by ltc on 2021/3/7.
//

#ifndef LIBPTHREAD_THREAD_H
#define LIBPTHREAD_THREAD_H

#include <pthread.h>

class Thread {
public:
    Thread() = default;
    void run(void* handle(void*), void* arg);
    void join();
    void detach();
    void cancel();
    pthread_t getID() const;
    bool getState() const;
    void* getResult() const;
    Thread(const Thread&) = delete;
    void operator=(const Thread&) = delete;
private:
    bool isRunning;
    pthread_t threadID;
    void* result;
};


#endif //LIBPTHREAD_THREAD_H
