#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include <time.h>

using namespace std;
using namespace chrono;
int main() {
    using my_engine = default_random_engine;
    using my_distribute = uniform_int_distribution<>;

    // auto t1 = high_resolution_clock::now();
    // auto ts = time_point_cast<seconds>(t1);
    my_engine re {random_device{}()};
    my_distribute one_to_six {1,6};

    auto die = bind(one_to_six, re);
    int x = die();
    x = die();
    cout << x << endl;
    return 0;
}