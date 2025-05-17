#include <iostream>
#include <type_traits>
#include <utility>

// 编译时计算斐波那契数列的模板实现
template<size_t N>
struct Fibonacci {
    // 使用 constexpr 静态成员确保编译时计算
    static constexpr size_t value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

// 特化版本：F(0) = 0
template<>
struct Fibonacci<0> {
    static constexpr size_t value = 0;
};

// 特化版本：F(1) = 1
template<>
struct Fibonacci<1> {
    static constexpr size_t value = 1;
};

// 运行时计算斐波那契数列的 constexpr 函数
constexpr size_t fibonacci(size_t n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

// 编译时获取斐波那契数列的辅助函数
template<size_t... Ns>
constexpr void print_sequence(std::index_sequence<Ns...>) {
    ((std::cout << "F(" << Ns << ") = " << Fibonacci<Ns>::value << '\n'), ...);
}

int main() {
    std::cout << "编译时计算的斐波那契数列（使用模板）：\n";
    print_sequence(std::make_index_sequence<10>());

    std::cout << "\n运行时计算的斐波那契数列（使用constexpr函数）：\n";
    for(size_t i = 0; i < 10; ++i) {
        // constexpr 函数也可以在运行时使用
        std::cout << "F(" << i << ") = " << fibonacci(i) << '\n';
    }

    static_assert(Fibonacci<5>::value == 5, "Fibonacci<5> should be 5");
    static_assert(fibonacci(5) == 5, "Fibonacci<5> should be 5");

    return 0;
}
