#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void print(const std::string& message, const std::vector<int>& vec) {
    std::cout << message;
    for (int x : vec) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

int main() {
    // 准备测试数据：包含重复元素的向量
    std::vector<int> vec = {1, 1, 2, 2, 3, 3, 3, 4, 5, 5, 5, 1, 1};
    print("原始序列: ", vec);

    // 方式1：使用 std::unique
    {
        std::cout << "\n方式1：使用 std::unique\n";
        auto vec_copy = vec;  // 创建副本进行测试
        
        // 首先需要排序，因为unique只移除相邻的重复元素
        std::sort(vec_copy.begin(), vec_copy.end());
        print("排序后: ", vec_copy);
        
        // unique返回新的逻辑末尾，需要用erase删除后面的元素
        auto new_end = std::unique(vec_copy.begin(), vec_copy.end());
        vec_copy.erase(new_end, vec_copy.end());
        
        print("去重后: ", vec_copy);
    }

    // 方式2：使用 std::unique_copy
    {
        std::cout << "\n方式2：使用 std::unique_copy\n";
        auto vec_copy = vec;  // 创建副本进行测试
        std::vector<int> result;
        
        // 首先排序
        std::sort(vec_copy.begin(), vec_copy.end());
        print("排序后: ", vec_copy);
        
        // 使用unique_copy直接复制到新容器，跳过重复元素
        std::unique_copy(vec_copy.begin(), vec_copy.end(), 
                        std::back_inserter(result));
        
        print("去重后: ", result);
    }

    // 方式3：不排序，直接删除相邻重复元素
    {
        std::cout << "\n方式3：直接删除相邻重复（不排序）\n";
        auto vec_copy = vec;
        print("原序列: ", vec_copy);
        
        // 直接使用unique删除相邻重复元素
        auto new_end = std::unique(vec_copy.begin(), vec_copy.end());
        vec_copy.erase(new_end, vec_copy.end());
        
        print("删除相邻重复后: ", vec_copy);
    }

    return 0;
}
