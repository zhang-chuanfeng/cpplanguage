#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

class SpinLock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            // 自旋等待
        }
    }
    
    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

// 测试自旋锁
void test_spinlock() {
    SpinLock spin;
    int shared_data = 0;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&spin, &shared_data]() {
            spin.lock();
            // 临界区
            ++shared_data;
            std::cout << "线程 " << std::this_thread::get_id() 
                     << " 修改数据为: " << shared_data << std::endl;
            spin.unlock();
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    test_spinlock();
    return 0;
}