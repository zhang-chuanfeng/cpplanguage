// 1. cin.exceptions() 设置会持续有效，直到被显式更改
// 在库代码中使用时，建议保存和恢复原始设置

// 2. cin出错后, cin会进入错误状态，这时cin的输入流会被关闭，
//不能再使用cin进行输入，需要使用cin.clear()清除错误状态，cin.ignore()清空输入缓冲区


#include <iostream>
#include <limits>
#include <string>
#include <exception>

using namespace std;

// 1. 通过状态标志检查
void test_status_flags() {
    cout << "\n=== 状态标志检查 ===\n";
    int number;
    
    cout << "请输入一个整数: ";
    cin >> number;
    
    if (cin.fail()) {
        cout << "输入错误！\n";
        // 清除错误状态
        cin.clear();
        // 清空输入缓冲区
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        cout << "输入的数字是: " << number << '\n';
    }
}

// 2. 使用异常处理
void test_exception_handling() {
    cout << "\n=== 异常处理 ===\n";
    int number;
    
    ios::iostate old_exceptions = cin.exceptions();

    cout << "请输入一个整数: ";
    cin.exceptions(old_exceptions | ios::failbit | ios::badbit);  // 启用异常
    
    try {
        cin >> number;
        cout << "输入的数字是: " << number << '\n';
    }
    catch (const ios_base::failure& e) {
        cout << "输入错误：" << e.what() << '\n';
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // 恢复原来的异常状态
    cin.exceptions(old_exceptions);
}

// 3. 循环验证输入
void test_input_validation() {
    cout << "\n=== 循环验证输入 ===\n";
    int number;
    bool valid_input = false;
    
    do {
        cout << "请输入一个整数: ";
        if (cin >> number) {
            valid_input = true;
        } else {
            cout << "输入无效，请重试\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!valid_input);
    
    cout << "输入的数字是: " << number << '\n';
}


int main() {
    test_status_flags();
    test_exception_handling();
    test_input_validation();
    return 0;
}