#include <iostream>

using namespace std;

template<typename T>
int byte_diff(T* p, T* q) {
    return reinterpret_cast<char *>(q) - reinterpret_cast<char *>(p);
}

void diff_test() {
    int vi[10];
    short vs[10];

    cout << vi << ' ' << &vi[1] << ' ' << &vi[1] - &vi[0] << ' ' << byte_diff(&vi[0], &vi[1]) << endl;
    cout << vs << ' ' << &vs[1] << ' ' << &vs[1] - &vs[0] << ' ' << byte_diff(&vs[0], &vs[1]) << endl;
}


int main() {
    diff_test();
}