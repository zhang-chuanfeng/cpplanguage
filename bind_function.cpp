#include <iostream>
#include <functional>
#include <string>

class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    
    // 带有this指针的成员函数
    void printResult(const std::string& op, double result) {
        std::cout << "计算结果 " << op << ": " << result << std::endl;
    }
};

// 普通函数
void globalPrint(const std::string& prefix, int value) {
    std::cout << prefix << value << std::endl;
}

int main() {
    Calculator calc;
    
    // 1. 绑定成员函数到 std::function
    std::function<int(int, int)> adder = std::bind(&Calculator::add, &calc, 
        std::placeholders::_1, std::placeholders::_2);
    
    // 使用固定参数绑定
    std::function<int(int)> addFive = std::bind(&Calculator::add, &calc, 
        std::placeholders::_1, 5);
    
    // 2. 绑定带有this指针的成员函数
    std::function<void(const std::string&, double)> printer = 
        std::bind(&Calculator::printResult, &calc, 
            std::placeholders::_1, std::placeholders::_2);
    
    // 3. 绑定普通函数
    std::function<void(int)> globalPrinter = 
        std::bind(globalPrint, "结果是: ", std::placeholders::_1);
    
    // 4. 使用 lambda 创建 function
    std::function<double(double)> multiplyByTwo = 
        [&calc](double x) { return calc.multiply(x, 2.0); };
    
    // 测试所有绑定
    std::cout << "===== 测试函数绑定 =====" << std::endl;
    
    int sum = adder(10, 20);
    std::cout << "10 + 20 = " << sum << std::endl;
    
    int result = addFive(10);
    std::cout << "10 + 5 = " << result << std::endl;
    
    printer("加法", sum);
    globalPrinter(result);
    
    double multiplied = multiplyByTwo(3.14);
    std::cout << "3.14 * 2 = " << multiplied << std::endl;
    
    return 0;
}