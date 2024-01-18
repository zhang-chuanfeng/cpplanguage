
// map
// 平衡二叉树   红黑树
// O(log(n))

// 哈希容器  无序容器
// unordered_map

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Entry {
    string name;
    int number;
};


bool operator<(const Entry& x, const Entry y) {
    return x.name < y.name;
}

bool operator==(const Entry& x, const Entry y) {
    return x.name == y.name && x.number == y.number;
}

list<Entry> f(vector<Entry>& vec) {
    list<Entry> res;
    sort(vec.begin(), vec.end()); // <
    unique_copy(vec.begin(), vec.end(), back_inserter(res)); // 追加到res 没有显式内存管理如realloc
    return res; // list移动构造
}


// 使用迭代器

bool has_c(const string& s, char c) {
    auto p = find(s.begin(), s.end(), c);
    if (p!=s.end())
        return true;
    else
        return false;
}

bool has_c2(const string& s, char c) {
    return find(s.begin(), s.end(), c) != s.end();
}


template<typename T>
using Iterator = typename T::iterator;

template<typename C, typename V>
std::vector<Iterator<C>> find_all(C& c, V v) {
    vector<Iterator<C>> res;
    for (auto p=c.begin(); p!=c.end(); ++p)
        if (*p == v)
            res.push_back(p);
    return res;
}

void test() {
    string m {"Mary had a little lamb"};
    // 范围for
    for (auto p : find_all(m, 'a')) // p 是一个string::iterator
        if (*p != 'a')
            cerr << "string bug!\n";

    list<double> ld {1.1, 2.2, 3.3, 1.1};
    for (auto p : find_all(ld, 1.1))
        if (*p != 1.1)
            cerr << "list bug!\n";
}

int main() {
    test();
}