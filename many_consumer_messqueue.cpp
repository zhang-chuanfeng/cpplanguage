#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <atomic>
#include <vector>
#include <optional>

template<typename T>
class MessageQueue {
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    const size_t capacity_;
    std::atomic<bool> running_{true};  // 添加停止标志
    std::atomic<size_t> total_produced_{0};  // 统计生产数量
    std::atomic<size_t> total_consumed_{0};  // 统计消费数量

public:
    explicit MessageQueue(size_t capacity = 100) : capacity_(capacity) {}

    // 批量发送消息
    bool send_batch(std::vector<T>& msgs) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_) return false;

        while (running_ && !msgs.empty()) {
            not_full_.wait(lock, [this]() { 
                return queue_.size() < capacity_ || !running_; 
            });
            
            if (!running_) return false;

            size_t space = capacity_ - queue_.size();
            size_t to_push = std::min(space, msgs.size());
            
            for (size_t i = 0; i < to_push; ++i) {
                queue_.push(std::move(msgs[i]));
                total_produced_++;
            }
            
            msgs.erase(msgs.begin(), msgs.begin() + to_push);
            not_empty_.notify_all();
        }
        return true;
    }

    // 批量接收消息
    size_t receive_batch(std::vector<T>& msgs, size_t max_msgs, 
                        const std::chrono::milliseconds& timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        
        bool received = not_empty_.wait_for(lock, timeout, [this]() { 
            return !queue_.empty() || !running_; 
        });
        
        if (!received || (!running_ && queue_.empty())) {
            return 0;
        }

        size_t count = std::min(max_msgs, queue_.size());
        for (size_t i = 0; i < count; ++i) {
            msgs.push_back(std::move(queue_.front()));
            queue_.pop();
            total_consumed_++;
        }
        
        if (count > 0) {
            not_full_.notify_all();
        }
        
        return count;
    }

    // 优化后的单个消息发送
    bool send(T&& msg) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_) return false;

        not_full_.wait(lock, [this]() { 
            return queue_.size() < capacity_ || !running_; 
        });
        
        if (!running_) return false;
        
        queue_.push(std::forward<T>(msg));
        total_produced_++;
        not_empty_.notify_all();
        return true;
    }

    // 优化后的单个消息接收
    std::optional<T> receive(const std::chrono::milliseconds& timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        
        bool received = not_empty_.wait_for(lock, timeout, [this]() { 
            return !queue_.empty() || !running_; 
        });
        
        if (!received || (!running_ && queue_.empty())) {
            return std::nullopt;
        }
        
        T msg = std::move(queue_.front());
        queue_.pop();
        total_consumed_++;
        not_full_.notify_all();
        return msg;
    }

    // 停止队列
    void stop() {
        std::unique_lock<std::mutex> lock(mutex_);
        running_ = false;
        not_empty_.notify_all();
        not_full_.notify_all();
    }

    // 获取统计信息
    std::pair<size_t, size_t> get_stats() const {
        return {total_produced_, total_consumed_};
    }
};

void test_multi_producer_consumer() {
    MessageQueue<std::string> queue(100);
    const int producer_count = 3;
    const int consumer_count = 2;
    const int msgs_per_producer = 1000;
    
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;
    
    // 启动生产者
    for (int p = 0; p < producer_count; ++p) {
        producers.emplace_back([&queue, p, msgs_per_producer]() {
            for (int i = 0; i < msgs_per_producer; ++i) {
                std::string msg = "P" + std::to_string(p) + 
                                ":Msg" + std::to_string(i);
                queue.send(std::move(msg));
            }
        });
    }
    
    // 启动消费者
    for (int c = 0; c < consumer_count; ++c) {
        consumers.emplace_back([&queue, c]() {
            std::vector<std::string> batch;
            while (true) {
                batch.clear();
                size_t received = queue.receive_batch(
                    batch, 10, std::chrono::milliseconds(100));
                    
                if (received == 0) {
                    // 检查是否所有消息都已处理完
                    auto [produced, consumed] = queue.get_stats();
                    if (produced == consumed) break;
                }
                
                for (const auto& msg : batch) {
                    std::cout << "Consumer " << c << " processed: " 
                            << msg << std::endl;
                }
            }
        });
    }
    
    // 等待所有生产者完成
    for (auto& p : producers) {
        p.join();
    }
    
    // 等待所有消费者完成
    for (auto& c : consumers) {
        c.join();
    }
    
    // 输出统计信息
    auto [produced, consumed] = queue.get_stats();
    std::cout << "Total produced: " << produced << std::endl;
    std::cout << "Total consumed: " << consumed << std::endl;
}

int main() {
    test_multi_producer_consumer();
    return 0;
}