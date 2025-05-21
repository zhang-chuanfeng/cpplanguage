#include <iostream>
#include <memory>
#include <algorithm>
#include <chrono>
#include <vector>

// RAII包装器for临时缓冲区
template<typename T>
class TemporaryBuffer {
public:
    explicit TemporaryBuffer(std::ptrdiff_t size) {
        // 使用 tie 来解构 pair
        std::tie(buffer_, size_) = std::get_temporary_buffer<T>(size);
    }

    // 禁用拷贝
    TemporaryBuffer(const TemporaryBuffer&) = delete;
    TemporaryBuffer& operator=(const TemporaryBuffer&) = delete;

    // 移动构造和赋值
    TemporaryBuffer(TemporaryBuffer&& other) noexcept
        : buffer_(other.buffer_), size_(other.size_) {
        other.buffer_ = nullptr;
        other.size_ = 0;
    }

    TemporaryBuffer& operator=(TemporaryBuffer&& other) noexcept {
        if (this != &other) {
            free();
            buffer_ = other.buffer_;
            size_ = other.size_;
            other.buffer_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // 析构函数中释放缓冲区
    ~TemporaryBuffer() {
        free();
    }

    // 访问器
    T* get() const { return buffer_; }
    std::ptrdiff_t size() const { return size_; }
    bool valid() const { return buffer_ != nullptr && size_ > 0; }

    // 迭代器支持
    T* begin() { return buffer_; }
    T* end() { return buffer_ + size_; }
    const T* begin() const { return buffer_; }
    const T* end() const { return buffer_ + size_; }

private:
    void free() {
        if (buffer_) {
            std::return_temporary_buffer(buffer_);
            buffer_ = nullptr;
            size_ = 0;
        }
    }

    T* buffer_ = nullptr;
    std::ptrdiff_t size_ = 0;
};

// 使用RAII包装的优化排序函数
template<typename Iterator>
void optimized_sort_raii(Iterator first, Iterator last) {
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    auto len = std::distance(first, last);
    
    // 使用RAII包装器创建临时缓冲区
    TemporaryBuffer<value_type> buffer(len);
    
    if (buffer.valid()) {
        // 使用范围for或迭代器进行操作
        std::copy(first, last, buffer.begin());
        std::sort(buffer.begin(), buffer.end());
        std::copy(buffer.begin(), buffer.end(), first);
    } else {
        std::sort(first, last);
    }
    // 缓冲区会在作用域结束时自动释放
}

// 性能测试函数
void performance_test_raii(size_t size) {
    std::vector<int> vec1(size), vec2(size);
    
    // 使用相同的随机数填充
    for (size_t i = 0; i < size; ++i) {
        vec1[i] = vec2[i] = rand();
    }
    
    // 测试标准排序
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(vec1.begin(), vec1.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto std_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // 测试RAII版本的优化排序
    start = std::chrono::high_resolution_clock::now();
    optimized_sort_raii(vec2.begin(), vec2.end());
    end = std::chrono::high_resolution_clock::now();
    auto opt_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "RAII版本测试 - 数据大小: " << size << " 元素\n";
    std::cout << "标准排序时间: " << std_duration.count() << " 微秒\n";
    std::cout << "优化排序时间: " << opt_duration.count() << " 微秒\n";
    std::cout << "结果相同: " << (vec1 == vec2) << "\n\n";
}

int main() {
    performance_test_raii(1000);
    performance_test_raii(10000);
    performance_test_raii(100000);
    return 0;
}