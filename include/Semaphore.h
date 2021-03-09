//
// Created by ltc on 2021/3/9.
//

#ifndef LIBPTHREAD_SEMAPHORE_H
#define LIBPTHREAD_SEMAPHORE_H

#include <semaphore.h>

class Semaphore {
public:
    Semaphore(int num);
    void wait();
    void post();
    ~Semaphore();
    Semaphore(const Semaphore&) = delete;
    void operator=(const Semaphore&) = delete;
private:
    sem_t semaphore;
};


#endif //LIBPTHREAD_SEMAPHORE_H
