#include <iostream>

using namespace std;

template<typename Iter>
using value_type = typename iterator_traits<Iter>::value_type;

template<typename Iter>
value_type<Iter> sum(Iter first, Iter last)
{
    value_type<Iter> s;
    while (first != last) {
        s += *first;
        ++first;
    }
    return s;
}
int main()
try
{
    cout << "Hello, world!" << endl;
    double ad[] = {1, 2, 3, 4, 5};
    double s = sum(ad, ad + 5);
    cout << s << endl;
    return 0;
}
catch (const exception &e)
{
    cerr << e.what() << endl;
    return 1;
}
catch (...)
{
    cerr << "Oops: unknown exception!" << endl;
    return 2;
}