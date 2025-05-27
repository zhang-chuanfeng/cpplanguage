#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>

template<typename T>
class MessageQueue {
private:
    std::queue<T> queue_;              // 消息队列
    mutable std::mutex mutex_;         // 互斥锁
    std::condition_variable not_empty_; // 非空条件变量
    std::condition_variable not_full_;  // 非满条件变量
    size_t capacity_;                  // 队列容量

public:
    explicit MessageQueue(size_t capacity = 100) : capacity_(capacity) {}

    // 发送消息（生产者）
    void send(T&& msg) {
        std::unique_lock<std::mutex> lock(mutex_);
        // 等待队列不满
        not_full_.wait(lock, [this]() { 
            return queue_.size() < capacity_; 
        });
        
        queue_.push(std::forward<T>(msg));
        // 通知消费者
        not_empty_.notify_one();
    }

    // 接收消息（消费者）
    T receive() {
        std::unique_lock<std::mutex> lock(mutex_);
        // 等待队列非空
        not_empty_.wait(lock, [this]() { 
            return !queue_.empty(); 
        });
        
        T msg = std::move(queue_.front());
        queue_.pop();
        // 通知生产者
        not_full_.notify_one();
        return msg;
    }

    // 尝试接收消息，带超时
    bool try_receive(T& msg, const std::chrono::milliseconds& timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!not_empty_.wait_for(lock, timeout, [this]() { 
            return !queue_.empty(); 
        })) {
            return false;
        }
        
        msg = std::move(queue_.front());
        queue_.pop();
        not_full_.notify_one();
        return true;
    }

    // 获取当前队列大小
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    // 检查队列是否为空
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }
};

void test_message_queue() {
    MessageQueue<std::string> queue(5); // 创建容量为5的消息队列

    // 生产者线程
    std::thread producer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            std::string msg = "消息 " + std::to_string(i);
            std::cout << "生产: " << msg << std::endl;
            queue.send(std::move(msg));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    // 消费者线程
    std::thread consumer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            std::string msg;
            if (queue.try_receive(msg, std::chrono::milliseconds(500))) {
                std::cout << "消费: " << msg << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    });

    producer.join();
    consumer.join();
}

int main() {
    test_message_queue();
    return 0;
}