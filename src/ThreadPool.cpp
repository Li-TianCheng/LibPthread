//
// Created by ltc on 2021/3/7.
//

#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(int threadNum, int queueSize):mutex(), condition(), queueSize(queueSize),
runningNum(0), shutdown(0), threadPool(threadNum){
    run();
}

void ThreadPool::addTask(void (*task)(void *), void *arg) {
    if (shutdown > 0){
        std::cout << "线程池正在关闭" << std::endl;
        return;
    }
    mutex.lock();
    while(taskQueue.size() == queueSize){
        condition.wait(mutex);
    }
    taskQueue.push(TaskNode(task, arg));
    condition.notifyAll(mutex);
}

void ThreadPool::run() {
    for(auto& thread : threadPool){
        thread.run(taskRoutine, (void*)this);
    }
}

void ThreadPool::close() {
    shutdown = 2;
    for (auto& thread : threadPool){
        thread.cancel();
        thread.detach();
    }
}

void ThreadPool::join() {
    shutdown = 1;
    for (auto& thread : threadPool){
        thread.cancel();
        thread.join();
    }
}

int ThreadPool::getRunningNum() const {
    return runningNum;
}

void ThreadPool::cleanHandler(void *arg) {
    ((ThreadPool*)arg)->mutex.unlock();
    ((ThreadPool*)arg)->runningNum--;
}

void* ThreadPool::taskRoutine(void *arg) {
    pthread_cleanup_push(cleanHandler, arg);
    ThreadPool* curr = (ThreadPool*)arg;
    while (true) {
        curr->mutex.lock();
        while (curr->shutdown == 2 || curr->taskQueue.empty()){
            curr->condition.wait(curr->mutex);
        }
        TaskNode t = curr->taskQueue.front();
        curr->taskQueue.pop();
        curr->condition.notifyAll(curr->mutex);
        curr->runningNum++;
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
        t.task(t.arg);
        pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, nullptr);
        curr->runningNum--;
    }
    pthread_cleanup_pop(0);
}

ThreadPool::~ThreadPool() {
    while(runningNum+threadPool.size() != 0){}
}
