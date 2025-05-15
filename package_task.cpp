#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <atomic>

class CustomTask {
public:
    CustomTask() : data(0) {}

    void process(int n) {
        std::cout << "开始处理任务，参数: " << n << std::endl;
        if (n < 0) {
            throw std::runtime_error("参数不能为负数！");
        }
        for (int i = 0; i < n; ++i) {
            // data.fetch_add(i, std::memory_order_relaxed); // 原子加法
            ++data;
            std::cout << "处理中，当前 data = " << data.load() << std::endl;
        }
        std::cout << "任务处理完成！最终 data = " << data.load() << std::endl;
    }

    int getData() const {
        return data.load(); // 原子读取
    }

private:
    std::atomic<int> data; // 使用原子变量
};

int main() {
    CustomTask taskObject;

    // 创建多个任务，操作同一个对象
    std::packaged_task<void(int)> task1([&taskObject](int n) {
        taskObject.process(n);
    });
    std::packaged_task<void(int)> task2([&taskObject](int n) {
        taskObject.process(n);
    });

    // 获取与任务关联的 future
    std::future<void> result1 = task1.get_future();
    std::future<void> result2 = task2.get_future();

    // 将任务交给多个线程执行
    std::thread t1([&]() {
        task1(5);
    });
    std::thread t2(std::move(task2), 3);

    // 等待任务完成并捕获异常
    try {
        std::cout << "等待任务1完成..." << std::endl;
        result1.get(); // 等待任务1完成
        std::cout << "任务1已完成！" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "任务1执行过程中捕获异常: " << e.what() << std::endl;
    }

    try {
        std::cout << "等待任务2完成..." << std::endl;
        result2.get(); // 等待任务2完成
        std::cout << "任务2已完成！" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "任务2执行过程中捕获异常: " << e.what() << std::endl;
    }

    // 确保线程完成
    t1.join();
    t2.join();

    // 主线程访问修改后的数据
    std::cout << "主线程中访问修改后的数据成员: " << taskObject.getData() << std::endl;

    return 0;
}
