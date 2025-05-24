#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << 42.0123123 << '\n';             // 输出：42
    // 长期有效的设置
    cout << "=== 长期有效的操纵符 ===\n";
    cout << hex << 16 << ' ' << 32 << '\n';  // 输出：10 20
    cout << 48 << '\n';  // 仍然是十六进制：30
    
    cout << dec;  // 恢复十进制
    
    // 临时有效的设置
    cout << "\n=== 临时有效的操纵符 ===\n";
    cout << setw(5) << 42 << '\n';     // 宽度为5
    cout << 42 << '\n';                // 正常宽度
    
    // 组合使用
    cout << "\n=== 组合使用 ===\n";
    cout << fixed << setprecision(2);  // fixed是长期的，setprecision也是长期的
    cout << 3.14159 << '\n';           // 输出：3.14
    cout << 2.71828 << '\n';           // 输出：2.72
    
    // 使用setf和unsetf手动控制
    cout.setf(ios::showpos);           // 显示正号
    cout << 42 << '\n';                // 输出：+42
    cout.unsetf(ios::showpos);         // 取消显示正号
    
    // 恢复默认流
    ostream default_stream(cout.rdbuf());
    cout.copyfmt(default_stream);

    cout << 42.0123123 << '\n';             // 输出：42
    return 0;
}