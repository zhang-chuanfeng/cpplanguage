#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 检查文件是否存在
    ifstream check_file("input.txt");
    if (!check_file.good()) {
        cerr << "Error: input.txt does not exist!\n";
        return 1;
    }
    check_file.close();

    // 从文件读取数据到容器
    ifstream input_file;
    input_file.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        input_file.open("input.txt");
        vector<int> numbers{
            istream_iterator<int>(input_file), 
            istream_iterator<int>()
        };
        input_file.close();

        // 将容器内容写入文件
        ofstream output_file("output.txt");
        if (!output_file) {
            cerr << "Error: Cannot create output.txt\n";
            return 1;
        }
        
        copy(numbers.begin(), numbers.end(), 
             ostream_iterator<int>(output_file, " "));
        
        cout << "Successfully processed " << numbers.size() << " numbers\n";
        
    } catch (const ifstream::failure& e) {
        cerr << "Exception during file operations: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}