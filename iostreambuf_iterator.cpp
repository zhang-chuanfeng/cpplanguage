#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main() {
    string data = "Hello World";

    // 使用流缓冲区迭代器复制字符
    copy(data.begin(), data.end(),
         ostreambuf_iterator<char>(cout));

    // 使用流缓冲区迭代器读取字符
    string result;
    copy(istreambuf_iterator<char>(cin),
         istreambuf_iterator<char>(),
         back_inserter(result));

    // 输出结果
    cout << "Result: " << result << endl;
    return 0;
}