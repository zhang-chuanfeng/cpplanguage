

// 编译时求值的函数


#include <limits>
#include <iostream>

// 编译期
constexpr float min = std::numeric_limits<float>::min();
constexpr int size = sizeof(int);
int main() {
    std::cout << "float min:" << min << "\n";
    std::cout << "int size:" << size << "\n";
    return 0;
}