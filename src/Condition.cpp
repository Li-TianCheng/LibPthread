//
// Created by ltc on 2021/3/7.
//

#include "Condition.h"
#include <stdexcept>
#include <sys/time.h>

Condition::Condition():flag(true){
    mutex = new Mutex();
    if (pthread_cond_init(&condition, nullptr) != 0){
        throw std::runtime_error("条件变量创建错误");
    }
}

void Condition::lock() {
    mutex->lock();
}

void Condition::unlock() {
    mutex->unlock();
}

void Condition::wait() {
    if (pthread_cond_wait(&condition, &(mutex->mutex)) != 0){
        throw std::runtime_error("条件变量等待错误");
    }
}

void Condition::wait(const unsigned int timeout) {
    struct timeval now;
    struct timespec tmpTimeout;
    gettimeofday(&now, nullptr);
    tmpTimeout.tv_sec = now.tv_sec + timeout / 1000;
    tmpTimeout.tv_nsec = now.tv_usec * 1000 + timeout % 1000 * 1000 * 1000;
    int status = pthread_cond_timedwait(&condition, &(mutex->mutex), &tmpTimeout);
    if (status == ETIMEDOUT) {
        return;
    }
    if (status != 0){
        throw std::runtime_error("条件变量等待错误");
    }
}

void Condition::notify() {
    if (pthread_cond_signal(&condition) != 0){
        throw std::runtime_error("条件变量唤醒错误");
    }
    unlock();
}

void Condition::notifyAll() {
    if (pthread_cond_broadcast(&condition) != 0){
        throw std::runtime_error("条件变量唤醒错误");
    }
    unlock();
}

Condition::~Condition(){
    if (flag){
        delete mutex;
    }
    pthread_cond_destroy(&condition);
}

Condition::Condition(Mutex& mutex):mutex(&mutex), flag(false){
    if (pthread_cond_init(&condition, nullptr) != 0){
        throw std::runtime_error("条件变量创建错误");
    }
}
