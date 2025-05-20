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
    // 测试数据
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print("原始序列: ", numbers);

    // 示例1：使用 partition 分离奇偶数
    {
        auto numbers_copy = numbers;
        std::cout << "\n示例1：分离奇偶数\n";
        
        // 按照奇数在前、偶数在后分区
        auto partition_point = std::partition(numbers_copy.begin(), numbers_copy.end(),
            [](int n) { return n % 2 == 1; });  // 奇数返回true
        
        print("分区后: ", numbers_copy);
        std::cout << "分区点位置: " << std::distance(numbers_copy.begin(), partition_point) << '\n';
        
        // 打印两个分区
        std::vector<int> odds(numbers_copy.begin(), partition_point);
        std::vector<int> evens(partition_point, numbers_copy.end());
        print("奇数部分: ", odds);
        print("偶数部分: ", evens);
    }

    // 示例2：使用 stable_partition 保持相对顺序
    {
        auto numbers_copy = numbers;
        std::cout << "\n示例2：使用stable_partition\n";
        
        // 按照大于5在前分区，保持原有相对顺序
        auto partition_point = std::stable_partition(numbers_copy.begin(), numbers_copy.end(),
            [](int n) { return n > 5; });
        
        print("稳定分区后: ", numbers_copy);
        std::cout << "分区点位置: " << std::distance(numbers_copy.begin(), partition_point) << '\n';
    }

    // 示例3：使用 partition_point 查找分区点
    {
        auto numbers_copy = numbers;
        std::cout << "\n示例3：使用partition_point\n";
        
        // 先分区
        std::partition(numbers_copy.begin(), numbers_copy.end(),
            [](int n) { return n < 6; });
        
        print("分区后: ", numbers_copy);
        
        // 使用partition_point找到分区点
        auto it = std::partition_point(numbers_copy.begin(), numbers_copy.end(),
            [](int n) { return n < 6; });
            
        std::cout << "分区点值: " << *it << '\n';
    }

    return 0;
}