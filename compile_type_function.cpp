#include <iostream>
#include <type_traits>
#include <memory>

// 栈内存存储的模板类
template<typename T>
class Scoped {
    T value_;
public:
    explicit Scoped(const T& value) : value_(value) {}
    Scoped(const Scoped&) = delete;
    Scoped& operator=(const Scoped&) = delete;

    T& operator*() { return value_; }
    const T& operator*() const { return value_; }
    T* operator->() { return &value_; }
    const T* operator->() const { return &value_; }
};

// 堆内存存储的模板类
template<typename T>
class On_heap {
    std::unique_ptr<T> ptr_;
public:
    explicit On_heap(const T& value) : ptr_(new T(value)) {}
    On_heap(const On_heap&) = delete;
    On_heap& operator=(const On_heap&) = delete;

    T& operator*() { return *ptr_; }
    const T& operator*() const { return *ptr_; }
    T* operator->() { return ptr_.get(); }
    const T* operator->() const { return ptr_.get(); }
};

// 主模板类，使用std::conditional选择存储类型
template<typename T, size_t N = 64>
class Obj_holder {
public:
    using type = typename std::conditional<sizeof(T)<=N,Scoped<T>,On_heap<T>>::type;
};

int main(int argc, char* argv[])
try
{
    // 测试代码
    struct Small { int x; };  // 4字节
    struct Large { int arr[100]; }; // 400字节

    // 对于小对象使用栈存储
    typename Obj_holder<Small>::type small(Small{42});
    // 对于大对象使用堆存储
    typename Obj_holder<Large>::type large(Large{});

    std::cout << "Small object value: " << (*small).x << std::endl;

    return 0;
}
catch (const std::exception &e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "Oops: unknown exception!\n";
    return 2;
}