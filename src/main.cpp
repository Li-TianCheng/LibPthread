#include <iostream>
#include <zconf.h>
#include "ThreadPool.h"

using namespace std;

int done = 0;
Mutex mutex;
void task(void* arg){
    usleep(500);
    mutex.lock();
    cout << "Tid:" << pthread_self() << "  " << done++ << endl;
    mutex.unlock();
}

int main() {
    int n = 100000;
    ThreadPool threadPool(10, 1000);
    for (int i = 0; i < n; i++){
        threadPool.addTask(task, nullptr);
    }
    threadPool.join();
    return 0;
}
