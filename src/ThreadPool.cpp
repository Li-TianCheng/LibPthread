//
// Created by ltc on 2021/3/7.
//

#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(int threadNum, int queueSize):threadNum(threadNum), condition(),
            queueSize(queueSize), runningNum(0), shutdown(false), threadPool(threadNum){
    run();
}

void ThreadPool::addTask(void (*task)(void *), void *arg) {
    if (shutdown){
        std::cout << "线程池正在关闭" << std::endl;
        return;
    }
    condition.lock();
    while(taskQueue.size() == queueSize){
        condition.wait();
    }
    taskQueue.push(TaskNode(task, arg));
    condition.notifyAll();
}

void ThreadPool::run() {
    for(auto& thread : threadPool){
        thread.run(taskRoutine, (void*)this);
    }
}

void ThreadPool::close() {
    shutdown = true;
    for (auto& thread : threadPool){
        thread.cancel();
        thread.detach();
    }
}

void ThreadPool::join() {
    shutdown = true;
    condition.lock();
    while (!taskQueue.empty()){
        condition.wait();
    }
    condition.unlock();
    for (auto& thread : threadPool){
        thread.cancel();
        thread.join();
    }
}

int ThreadPool::getRunningNum() const {
    return runningNum;
}

void ThreadPool::cleanHandler(void *arg) {
    ((ThreadPool*)arg)->condition.unlock();
}

void* ThreadPool::taskRoutine(void *arg) {
    pthread_cleanup_push(cleanHandler, arg);
    ThreadPool* curr = (ThreadPool*)arg;
    while (true) {
        pthread_testcancel();
        curr->condition.lock();
        while (curr->taskQueue.empty()){
            curr->condition.wait();
        }
        TaskNode t = curr->taskQueue.front();
        curr->taskQueue.pop();
        curr->condition.notifyAll();
        curr->runningNum++;
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
        t.task(t.arg);
        pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, nullptr);
        curr->runningNum--;
    }
    pthread_cleanup_pop(0);
}
