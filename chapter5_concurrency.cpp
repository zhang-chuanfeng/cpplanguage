
// 资源管理

// unique_ptr
// shared_ptr

// 并发
// 标准库提供单一地址空间内并发执行多个线程
// 标准库提供系统级并发机制  不直接提供复杂的高层并发模型

// thread mutex lock  package_task future

// 共享数据
// mutex unique_lock

// unique_lock<mutex> lck1 {m1, defer_lock};
// unique_lock<mutex> lck2 {m2, defer_lock};
// unique_lock<mutex> lck3 {m3, defer_lock};
// lock(lck1, lck2, lck3); // 同时获取到3把锁才会执行


// 等待事件
// sleep_for  chrono

// condition_variable


// class Message {
//};
// queue<Message> mqueue;
// condition_variable mcond;
// mutex mmutex;

// void consumer() {
//  while(true) {
//      unique_lock<mutex> lck{mmutex}; // 获取mutex
//      while(mcond.wait(lck)) /*do nothing */  // 释放lck并等待
//      // 被唤醒后重新获取lck
//      auto m = mqueue.front();
//      mqueue.pop();
//      lck.unlock      // 释放lck
//      // 处理m
//  }
//}

// void producer() {
//  while(true) {
//      Message m;
//      // 填入消息
//      unique_lock<mutex> lck {mmutex}; // 保护队列上的操作
//      mqueue.push(m);
//      mcond.notify_one();              // 通知
//  }                                    // 释放锁(在作用域结束)
//}

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;

void test_chrono() {
   auto t0 = high_resolution_clock::now();
   std::this_thread::sleep_for(milliseconds{20});
   auto t1 = high_resolution_clock::now();
   std::cout << duration_cast<milliseconds>(t1 - t0).count() << std::endl;
}

int main() {
    test_chrono();
    return 0;
}