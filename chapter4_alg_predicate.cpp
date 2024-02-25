#include <algorithm>
#include <string>
#include <map>

using namespace std;

// 函数对象

struct Greater_than {
    int val;
    Greater_than(int v): val{v} {}
    bool operator()(const pair<string, int> &r) {return r.second > 42;}
};

void test() {
    map<string,int> m{{"1", 1}, {"2", 2}};

    find_if(m.begin(), m.end(), Greater_than{42});
}

void test2() {
    map<string,int> m{{"1", 1}, {"2", 2}};

    find_if(m.begin(), m.end(), [](const pair<string, int> &r){ return r.second > 42;});
}

int main()
{
    test();
    test2();
}