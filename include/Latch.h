//
// Created by ltc on 2021/5/8.
//

#ifndef LIBPTHREAD_LATCH_H
#define LIBPTHREAD_LATCH_H

#include "Mutex.h"
#include "Condition.h"

class Latch {
public:
    explicit Latch(int num);
    void done();
    void wait();
    Latch(const Latch&) = delete;
    Latch(Latch&&) = delete;
    void operator=(const Latch&) = delete;
    void operator=(Latch&&) = delete;
private:
    int count;
    Mutex mutex;
    Condition condition;
};


#endif //LIBPTHREAD_LATCH_H
