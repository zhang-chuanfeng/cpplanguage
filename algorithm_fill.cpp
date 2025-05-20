#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int v1[900];
array<int,900> v2;
vector<int> v3;

int main(int argc, char* argv[])
try
{
    std::cout << "Hello, world!" << std::endl;
    fill(begin(v1), end(v1), 99);
    generate(begin(v2), end(v2), []() { return rand(); } );
    generate_n(ostream_iterator<int>{cout, " "}, 10, []() { return rand(); } );
    cout << endl;
    fill_n(back_inserter(v3), 10, 99);
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
