#include <iostream>
#include "ThreadPool.h"
#include <chrono>

using namespace std;
using namespace chrono;

void task(void* arg){
    int sum = 0;
    for (int i = 0; i < 1000000; i++)
        sum++;
}

int main() {
    int n = 10000;
    auto start = system_clock::now();
    ThreadPool threadPool(12, 1000);
    for (int i = 0; i < n; i++){
        threadPool.addTask(task, nullptr);
    }
    threadPool.join();
    auto duration = duration_cast<microseconds>(system_clock::now() - start);
    cout << double(duration.count()) * microseconds::period::num / microseconds::period::den  << endl;

    start = system_clock::now();
    for (int i = 0; i < n; i++) {
        task(nullptr);
    }
    duration = duration_cast<microseconds>(system_clock::now() - start);
    cout << double(duration.count()) * microseconds::period::num / microseconds::period::den  << endl;
    return 0;
}
