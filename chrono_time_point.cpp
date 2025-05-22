#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
int main(int argc, char* argv[])
try
{
    // system_clock 是系统的壁钟时间，它的纪元（epoch）通常是 1970年1月1日 UTC
    auto tp = system_clock::now();
    auto d1 = time_point_cast<hours>(tp).time_since_epoch().count()/24;

    using days = duration<long,ratio<24*60*60,1>>;
    auto d2 = time_point_cast<days>(tp).time_since_epoch().count();
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    return 0;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "Oops: unknown exception!" << std::endl;
    return 2;
}
