#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

class LockFreeFlag {
    std::atomic_flag initialized = ATOMIC_FLAG_INIT;
public:
    void initialize() {
        if (!initialized.test_and_set()) {
            // 只有第一个线程会执行这里
            std::cout << "执行一次性初始化" << std::endl;
        }
    }
};

void test_lockfree_flag() {
    LockFreeFlag flag;
    std::vector<std::thread> threads;
    
    // 多个线程尝试初始化
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&flag, i]() {
            std::cout << "线程 " << i << " 尝试初始化" << std::endl;
            flag.initialize();
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    test_lockfree_flag();
    return 0;
}