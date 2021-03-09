//
// Created by ltc on 2021/3/9.
//

#ifndef LIBPTHREAD_RWLOCK_H
#define LIBPTHREAD_RWLOCK_H

#include <pthread.h>

class RwLock {
public:
    RwLock();
    void rdLock();
    void wrLock();
    void unlock();
    bool tryRdLock();
    bool tryWrLock();
    ~RwLock();
    RwLock(const RwLock&) = delete;
    void operator=(const RwLock&) = delete;
private:
    pthread_rwlock_t  rwLock;
};


#endif //LIBPTHREAD_RWLOCK_H
