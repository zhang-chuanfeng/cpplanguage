#include <iostream>
#include <utility>
#include <string>
#include <tuple>

using namespace std;
int main() {
    pair<int,string> p {1, "test"};
    tuple<string,int,double> tp {"test", 1, 2.0};

    int p0 = get<0>(p);
    auto p1 = get<1>(p);
    auto tp0 = get<0>(tp);
    int tp1 = get<1>(tp);
    double tp2 = get<2>(tp);
    cout << "p0=" << p0 << endl; 
    cout << "p1=" << p1 << endl; 
    cout << "tp=" << tp0 << endl; 
    cout << "tp1=" << tp1 << endl; 
    cout << "tp2=" << tp2 << endl; 
    return 0;
}