#include <atomic>
#include <thread>
#include <iostream>
#include <chrono>

class Signal {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void wait() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
    }
    
    void notify() {
        flag.clear(std::memory_order_release);
    }
};

void test_signal() {
    Signal sig;

    // 工作线程
    std::thread worker([&]() {
        std::cout << "工作线程等待信号..." << std::endl;
        sig.wait();
        std::cout << "工作线程收到信号，开始工作" << std::endl;
    });
    
    // 主线程延迟后发送信号
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "主线程发送信号" << std::endl;
    sig.notify();
    
    worker.join();
}

int main() {
    test_signal();
    return 0;
}