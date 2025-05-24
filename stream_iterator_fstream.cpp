#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream input_file("input.txt");
    if (!input_file.good()) {
        std::error_code ec(errno, std::system_category()); // windows下不适合
        cerr << "打开文件失败: " << ec.message() << endl;
        return 1;
    }
    vector<int> numbers{
        istream_iterator<int>(input_file), 
        istream_iterator<int>()
    };

    // 将容器内容写入文件
    ofstream output_file("output.txt");
    copy(numbers.begin(), numbers.end(), 
         ostream_iterator<int>(output_file, " "));
    
    return 0;
}