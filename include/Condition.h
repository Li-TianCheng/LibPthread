//
// Created by ltc on 2021/3/7.
//

#ifndef LIBPTHREAD_CONDITION_H
#define LIBPTHREAD_CONDITION_H

#include "Mutex.h"

class Condition {
public:
    Condition();
    void wait(Mutex& mutex);
    void wait(Mutex& mutex, const unsigned int timeout);
    void notify(Mutex& mutex);
    void notifyAll(Mutex& mutex);
    ~Condition();
    Condition(const Condition&) = delete;
    void operator=(const Condition&) = delete;
private:
    pthread_cond_t condition;
};


#endif //LIBPTHREAD_CONDITION_H
