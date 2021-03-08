//
// Created by ltc on 2021/3/7.
//

#ifndef LIBPTHREAD_MUTEX_H
#define LIBPTHREAD_MUTEX_H

#include <pthread.h>

class Mutex {
public:
    Mutex();
    void lock();
    void unlock();
    bool tryLock();
    ~Mutex();
    Mutex(const Mutex&) = delete;
    void operator=(const Mutex&) = delete;
private:
    friend class Condition;
    pthread_mutex_t mutex;
};


#endif //LIBPTHREAD_MUTEX_H
