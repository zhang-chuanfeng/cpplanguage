#include <iostream>
#include <vector>

using namespace std;

template <typename X>
void myusr(const vector<X>& v) {
    constexpr int bufmax = 1024;
    alignas(X) X buff[bufmax];

    const int max = min(v.size(), bufmax/sizeof(X));
    uninitialized_copy(v.begin(), v.begin()+max, buff);
    for (int i = 0; i<max; i++) {
        cout << "buff["<<i <<"]="<< buff[i] << endl;
    }
}

int main() {
    auto ac = alignof('c');
    auto ai = alignof(1);
    auto ad = alignof(2.0);
    int a[20];
    auto aa = alignof(a);
    auto av = alignof(vector<double>);

    vector<int> vi {12,3,15,17};
    myusr(vi);
    cout << "ac=" << ac << ",ai=" << ai << ",ad=" << ad << ",aa=" << aa << ",av=" << av << endl;
}