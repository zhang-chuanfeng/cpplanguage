#include <string>
#include <iostream>
#include <vector>

void tmp_var() {
    std::string s1 = "12142";
    std::string s2 = "23425";

    const std::string& tmp_str = s1 + s2; // 引用临时对象
    std::cout << tmp_str << std::endl;
}

std::vector<std::string> aguments(int argc, char* argv[]) {
    std::vector<std::string> res;
    for (int i = 0; i < argc; ++i) {
        res.push_back(argv[i]);
    }
    return res; // 移动
}

int main(int argc, char* argv[]) {
    auto args = aguments(argc, argv);
    for (auto arg : args) {
        std::cout << arg << "\n";
    }
    tmp_var();
}