#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <type_traits>
#include <iterator>
#include <algorithm>  // 为 std::sort 添加头文件

// 主模板 - 用于检测是否有 begin() 和 end() 方法
template<typename T, typename = void>
struct HasBeginEnd : std::false_type {};

// 特化版本 - 当类型T有begin()和end()方法时
template<typename T>
struct HasBeginEnd<T, 
    std::void_t<
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
    >
> : std::true_type {};

// Range概念的包装器
template<typename Cont>
constexpr bool Range() {
    return HasBeginEnd<Cont>::value;
}

// 检查迭代器是否为随机访问迭代器的辅助类
template<typename, typename = void>
struct HasRandomAccess : std::false_type {};

template<typename T>
struct HasRandomAccess<T,
    std::void_t<
        typename std::iterator_traits<T>::iterator_category,
        std::enable_if_t<std::is_same_v<
            typename std::iterator_traits<T>::iterator_category,
            std::random_access_iterator_tag
        >>
    >
> : std::true_type {};

// Sortable概念的包装器
template<typename Cont>
constexpr bool Sortable() {
    if constexpr (!Range<Cont>()) {
        return false;
    } else {
        using Iterator = decltype(std::declval<Cont>().begin());
        return HasRandomAccess<Iterator>::value;
    }
}

// 容器版本的Sort函数模板
template<typename Container>
void Sort(Container& cont) {
    static_assert(Sortable<Container>(), "Container must be sortable (have random access iterator)");
    std::sort(cont.begin(), cont.end());
}

int main()
{
    // 验证 Range 概念
    static_assert(Range<std::vector<int>>(), "std::vector should be a Range");
    static_assert(Range<std::string>(), "std::string should be a Range");
    static_assert(Range<std::list<int>>(), "std::list should be a Range");
    
    // 验证 Sortable 概念
    static_assert(Sortable<std::vector<int>>(), "std::vector should be Sortable");
    static_assert(Sortable<std::string>(), "std::string should be Sortable");
    static_assert(!Sortable<std::list<int>>(), "std::list should not be Sortable");
    
    // 验证非Range非Sortable类型
    struct NonRange {};
    static_assert(!Range<NonRange>(), "NonRange should not be a Range");
    static_assert(!Sortable<NonRange>(), "NonRange should not be Sortable");
    
    // 运行时测试
    std::cout << std::boolalpha;
    
    std::vector<int> vec = {1, 2, 3};
    std::cout << "std::vector<int>:\n"
              << "  is Range: " << Range<std::vector<int>>() << '\n'
              << "  is Sortable: " << Sortable<std::vector<int>>() << '\n';
    
    std::list<int> lst = {1, 2, 3};
    std::cout << "\nstd::list<int>:\n"
              << "  is Range: " << Range<std::list<int>>() << '\n'
              << "  is Sortable: " << Sortable<std::list<int>>() << '\n';
    
    // NonRange nr;
    std::cout << "\nNonRange:\n"
              << "  is Range: " << Range<NonRange>() << '\n'
              << "  is Sortable: " << Sortable<NonRange>() << '\n';

    std::vector<int> vecToSort = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "\nvector Before sort: ";
    for (int i : vecToSort) std::cout << i << ' ';
    std::cout << '\n';
    
    Sort(vecToSort);  // 可以排序，因为 vector 是 Sortable
    
    std::cout << "vector After sort: ";
    for (int i : vecToSort) std::cout << i << ' ';
    std::cout << '\n';
    
    // std::list<int> lstToSort = {3, 1, 4, 1, 5};
    // Sort(lstToSort);  // 编译错误，因为 list 不是 Sortable
    
    // NonRange nr2;
    // Sort(nr2);  // 编译错误，因为 NonRange 不是 Sortable

    return 0;
}
