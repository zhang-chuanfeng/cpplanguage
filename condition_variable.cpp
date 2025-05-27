#include <condition_variable>
#include <mutex>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

// this_thread::wait_for大致实现
void simple_timer(int delay) {
    condition_variable timer;
    mutex mtx;
    auto t0 = chrono::steady_clock::now();
    unique_lock<mutex> lock(mtx); // 获得锁，析构释放锁
    timer.wait_for(lock, chrono::milliseconds(delay)); // 释放锁，线程休眠，超时唤醒获得锁
    auto t1 = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
    cout << "Waited for " << elapsed << " milliseconds." << endl;
}

int main() {
    simple_timer(1000); // 等待1秒
    return 0;
}