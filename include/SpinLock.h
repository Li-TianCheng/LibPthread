//
// Created by ltc on 2021/3/9.
//

#ifndef LIBPTHREAD_SPINLOCK_H
#define LIBPTHREAD_SPINLOCK_H

#include <pthread.h>

class SpinLock {
public:
    SpinLock();
    void lock();
    void unlock();
    bool tryLock();
    ~SpinLock();
    SpinLock(const SpinLock&) = delete;
    void operator=(const SpinLock&) = delete;
private:
    pthread_spinlock_t spinLock;
};


#endif //LIBPTHREAD_SPINLOCK_H
