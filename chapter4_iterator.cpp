
// 容器迭代器

// 流迭代器

// 迭代器--处理容器中元素序列 有用的通用概念

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// 流迭代器方便算法处理
ostream_iterator<string> oo {cout};
void test_ostream_iterator() {
    *oo = "Hello,";
    ++oo; // 没执行内容
    *oo = "world!\n";
}

// istream_iterator<string> ii {cin};
// istream_iterator<string> eos {};

int test_stream_iterator() {
    string from, to;
    cin >> from >> to;

    ifstream is {from};
    istream_iterator<string> iii {is};
    istream_iterator<string> ieos {};

    ofstream os {to};
    ostream_iterator<string> ooo {os, "\n"};

    vector<string> b {iii, ieos};   // 缓存
    cout << "sort before:\n";
    for (string& s : b) {
        cout << s << '\n';
    }
    sort(b.begin(), b.end());       // <
    cout << "sort out:\n";
    for (string& s : b) {
        cout << s << '\n';
    }

    unique_copy(b.begin(), b.end(), ooo);
    return !is.eof() || !os;
}

int test_stream_iterator_simple() {
    string from, to;
    cin >> from >> to;

    ifstream is {from};
    ofstream os {to};

    // 不保留重复值，并且进行排序
    set<string> b {istream_iterator<string>{is}, istream_iterator<string>{}};

    // 拷贝到cout
    copy(b.begin(), b.end(), ostream_iterator<string>{os, "\n"});
    return !is.eof() || !os;
}

int main() {
    test_ostream_iterator();
    test_stream_iterator();
    test_stream_iterator_simple();
}