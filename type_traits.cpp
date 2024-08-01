#include <type_traits>
#include <iostream>
#include <string>

int main() {
    bool a = std::is_arithmetic<int>();
    bool b = std::is_arithmetic<std::string>();

    std::cout << "a=" << a << std::endl;
    std::cout << "b=" << b << std::endl;
}