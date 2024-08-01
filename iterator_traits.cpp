
// iterator_traits  迭代器类型说明符

// 标准库sort参数迭代器必须随机访问迭代器

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

namespace Estd {
    using namespace std;

    template<class C>
    void sort(C& c) {
        sort(c.begin(), c.end());
    }

    template<class C, class Pre>
    void sort(C& c, Pre p) {
        sort(c.begin(), c.end(), p);
    }
}

namespace Estd2 {
    using namespace std;

    template<typename Ran>
    void sort_helper(Ran beg, Ran end, random_access_iterator_tag) {
        sort(beg, end);
    }

    // template <typename Iter>
    //     using Value_type = typename iterator_traits<Iter>::value_type;

    template<typename For>
    void sort_helper(For beg, For end, forward_iterator_tag) {
        // using T = Value_type<For>;
        using T = typename For::value_type;
        vector<T> v(beg, end);
        sort(v.begin(), v.end());
        copy(v.begin(), v.end(), beg);
    }

    template <typename C>
        using Iterator_type = typename C::iterator;
    template <typename Iter>
        using Iterator_category = typename iterator_traits<Iter>::iterator_category;
    template<class C>
    void sort(C& c) {
        using Iter = Iterator_type<C>;
        sort_helper(c.begin(), c.end(), Iterator_category<Iter>{});
    }
}

int main() {
    std::list<int> list {12, 1, 5, 34,56,78};
    // list.begin()
    // std::vector<int> tmp {list.begin(), list.end()};
    // std::sort(tmp.begin(), tmp.end());
    // Estd::sort(tmp);
    Estd2::sort(list);
    for (auto & n: list) {
        std::cout << n  << " ";
    }
    std::cout << "\n";
    return 0;
}