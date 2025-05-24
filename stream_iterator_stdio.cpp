#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    // 从标准输入读取数据直到EOF
    vector<string> words{
        istream_iterator<string>(cin),
        istream_iterator<string>()
    };

    // 输出到标准输出
    copy(words.begin(), words.end(),
         ostream_iterator<string>(cout, "\n"));
    
    return 0;
}