#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// 打印辅助函数
void print(const std::string& message, const std::vector<int>& vec) {
    std::cout << message;
    for (int x : vec) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

int main() {
    // 示例1：使用 next_permutation 生成所有排列
    {
        std::vector<int> numbers = {1, 2, 3};
        std::cout << "示例1：使用 next_permutation 生成所有排列\n";
        print("初始序列: ", numbers);
        
        // 生成所有可能的排列
        do {
            print("当前排列: ", numbers);
        } while (std::next_permutation(numbers.begin(), numbers.end()));
    }

    // 示例2：使用 prev_permutation 生成逆序排列
    {
        std::vector<int> numbers = {3, 2, 1};
        std::cout << "\n示例2：使用 prev_permutation 生成逆序排列\n";
        print("初始序列: ", numbers);
        
        // 生成所有可能的逆序排列
        do {
            print("当前排列: ", numbers);
        } while (std::prev_permutation(numbers.begin(), numbers.end()));
    }

    // 示例3：使用自定义比较函数
    {
        std::vector<int> numbers = {1, 2, 3};
        std::cout << "\n示例3：使用自定义比较函数生成排列\n";
        print("初始序列: ", numbers);
        
        // 使用大于比较生成排列
        do {
            print("当前排列: ", numbers);
        } while (std::next_permutation(numbers.begin(), numbers.end(), 
                 std::greater<int>()));
    }

    // 示例4：字符串排列
    {
        std::string str = "abc";
        std::cout << "\n示例4：字符串排列\n";
        std::cout << "初始字符串: " << str << '\n';
        
        // 生成字符串的所有排列
        do {
            std::cout << "当前排列: " << str << '\n';
        } while (std::next_permutation(str.begin(), str.end()));
    }

    return 0;
}