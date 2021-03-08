//
// Created by ltc on 2021/3/7.
//

#ifndef LIBPTHREAD_CONDITION_H
#define LIBPTHREAD_CONDITION_H

#include "Mutex.h"

class Condition {
public:
    Condition();
    explicit Condition(Mutex& mutex);
    void lock();
    void unlock();
    void wait();
    void wait(const unsigned int timeout);
    void notify();
    void notifyAll();
    ~Condition();
    Condition(const Condition&) = delete;
    void operator=(const Condition&) = delete;
private:
    pthread_cond_t condition;
    Mutex *mutex;
    bool flag;
};


#endif //LIBPTHREAD_CONDITION_H
